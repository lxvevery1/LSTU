using Ilya_lab2.Properties;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Resources;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace Ilya_lab2
{
    public partial class Form1 : Form
    {
        private List<Job> jobs = new List<Job>();
        private int maxTime;

        public Form1()
        {
            InitializeComponent();
            InitializeCharts();
        }

        private void InitializeChart1(int i)
        {
            chartRes1.Series[0].Points.Clear();
            chartRes1.Series[1].Points.Clear();
            chartRes2.Series[0].Points.Clear();
            chartRes2.Series[1].Points.Clear();
            chartRes3.Series[0].Points.Clear();
            chartRes3.Series[1].Points.Clear();

        }
        private void AddToChart(int i, int j, int x, int y)
        {
            if (i == 0)
            {
                if (j == 1)
                    chartRes1.Series[0].Points.AddXY(x+0.5, y);
                if (j == 2)
                    chartRes1.Series[1].Points.AddXY(x+0.5, y);
            }
            if (i == 1)
            {
                if (j == 1)
                    chartRes2.Series[0].Points.AddXY(x+0.5, y);
                if (j == 2)
                    chartRes2.Series[1].Points.AddXY(x+0.5, y);
            }
            if (i == 2)
            {
                if (j == 1)
                    chartRes3.Series[0].Points.AddXY(x+0.5, y);
                if (j == 2)
                    chartRes3.Series[1].Points.AddXY(x+0.5, y);
            }
        }
        private void InitializeCharts()
        {
            // Настройка диаграммы Ганта
            var ganttChartArea = new ChartArea("GanttChartArea");
            chartGantt.ChartAreas.Add(ganttChartArea);
            chartGantt.Series.Add(new Series("GanttSeries")
            {
                ChartType = SeriesChartType.RangeBar,
                CustomProperties = "DrawingStyle=Wedge, BarLabelStyle=Outside, PointWidth=1",
                MarkerBorderWidth = 0,
                Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.EarthTones,
                YValuesPerPoint = 2,
            });

            // Настройка осей для диаграммы Ганта
            ganttChartArea.AxisX.IsStartedFromZero = true; // Старт с нуля
            ganttChartArea.AxisX.Minimum = 1;
            ganttChartArea.AxisX.Interval = 1; // Интервал между метками на оси X
            ganttChartArea.AxisY.Interval = 1; // Интервал между метками на оси X
            ganttChartArea.AxisX.Title = "Работы";
            ganttChartArea.AxisY.Title = "Время";
            // Инициализируем диаграммы пустыми значениями
            InitializeEmptyCharts();
        }


        private void InitializeEmptyCharts()
        {
            chartGantt.Series["GanttSeries"].Points.Clear();
            chartGantt.ChartAreas[0].AxisX.Title = "Работы";
            chartGantt.ChartAreas[0].AxisY.Title = "Время";
            chartGantt.ChartAreas[0].RecalculateAxesScale();
        }

        // Новый метод для отображения исходного состояния на диаграммах
        private void DisplayInitialState(List<Job> jobs)
        {
            InitializeEmptyCharts(); // Сбрасываем диаграммы
            int EndTime = 0;
            if (jobs.Count == 0)
                return; // Если нет работ, выходим

            // Словарь для отслеживания времени окончания работ и их начала
            Dictionary<int, int> endEventTimes = new Dictionary<int, int>();

            // Логика для построения диаграммы Ганта
            foreach (var job in jobs)
            {
                // Определяем время начала работы
                int startTime;
                if (endEventTimes.ContainsKey(job.StartEvent))
                {
                    startTime = endEventTimes[job.StartEvent]; // Начинаем после соответствующего события
                }
                else
                {
                    startTime = 0; // Если нет события, начинаем с 0
                }

                int endTime = startTime + job.Duration; // Время окончания работы
                if (endTime >= EndTime)
                    EndTime = endTime;

                // Добавляем данные на диаграмму Ганта
                chartGantt.Series["GanttSeries"].Points.AddXY(job.Id+1.5, job.StartTime, job.EndTime);

            }
            EndTime = 0;
            foreach (var job in jobs)
            {
                if (job.EndTime > EndTime)
                    EndTime = job.EndTime;

            }
            chartGantt.ChartAreas["GanttChartArea"].AxisY.Maximum = EndTime;
            chartRes1.ChartAreas["ChartArea1"].AxisX.Maximum = EndTime;
            chartRes2.ChartAreas["ChartArea1"].AxisX.Maximum = EndTime;
            chartRes3.ChartAreas["ChartArea1"].AxisX.Maximum = EndTime;

            // Логика для отображения начального потребления ресурсов
            int[][] initialResourceUsage = new int[EndTime + 1][];
            // Подсчитываем потребление ресурсов для каждого момента времени
            int[] Res = new int[(int)rescount.Value];
            for (int i = 0; i < rescount.Value; i++)
            {
                Res[i] = Convert.ToInt16(res.Rows[i].Cells[0].Value);
            }
            for (int t = 0; t < EndTime && t <= EndTime; t++)
            {
                initialResourceUsage[t] = new int[(int)rescount.Value];
                for (int i = 0; i < rescount.Value; i++)
                {
                    initialResourceUsage[t][i] = 0;
                }
                // Суммируем потребление для всех работ, которые выполняются в момент t

                foreach (var job in jobs)
                {
                    if (job.StartTime <= t && t < job.StartTime + job.Duration)
                    {
                        for (int i = 0; i < rescount.Value; i++)
                        {
                            initialResourceUsage[t][i] += job.ResourceConsumption[i];
                        }
                    }
                }
            }

            // Заполняем диаграмму потребления ресурсов
            for (int t = 0; t < initialResourceUsage.Length-1; t++)
            {
                for (int i = 0; i < rescount.Value; i++)
                {
                    AddToChart(i, 1, t, Res[i]);
                    if (initialResourceUsage[t][i] > 0) // Добавляем только если есть потребление
                    {
                        AddToChart(i, 2, t, initialResourceUsage[t][i]);
                    }
                }
            }
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            // Инициализация таблицы ресурсов
            res_Label.RowCount = 1;
            res.RowCount = 1;
            res.ColumnCount = 2; // Увеличиваем количество столбцов до 2
            res_Label.Rows[0].Cells[0].Value = "1-й ресурс: ";

            // Инициализация заголовков таблицы ресурсов
            resHeader.RowCount = 1;
            resHeader.ColumnCount = 2;
            resHeader.Rows[0].Cells[0].Value = "Изначальное количество";
            resHeader.Rows[0].Cells[1].Value = "Приоритет";

            // Инициализация других таблиц
            res_labelHeader.RowCount = 1;
            jobHeader.RowCount = 1;
            jobHeader.ColumnCount = 3;
            job.ColumnCount = 3;
            job_labelHeader.RowCount = 1;
            job_label.RowCount = 1;
            job.RowCount = 1;
            jobres.RowCount = 1;
            jobresHeader.RowCount = 1;
            jobresHeader.Rows[0].Cells[0].Value = "1-й рес.";
            job_label.Rows[0].Cells[0].Value = (1).ToString() + "-я работа:";
            jobHeader.Rows[0].Cells[0].Value = "Начальное событие";
            jobHeader.Rows[0].Cells[1].Value = "Конечное событие";
            jobHeader.Rows[0].Cells[2].Value = "Длительность";
        }

        private void jobcount_ValueChanged(object sender, EventArgs e)
        {
            job.RowCount = (int)jobcount.Value;
            jobres.RowCount = (int)jobcount.Value;
            job_label.RowCount = (int)jobcount.Value;
            for (int i = 0; i < jobcount.Value; i++)
            {
                job_label.Rows[i].Cells[0].Value = (i+1).ToString()+"-я работа:";
            }
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            res_Label.RowCount = (int)rescount.Value;
            res.RowCount = (int)rescount.Value;
            jobresHeader.ColumnCount = (int)rescount.Value;
            jobres.ColumnCount = (int)rescount.Value;
            for (int i = 0; i < res_Label.RowCount; i++)
            {
                res_Label.Rows[i].Cells[0].Value = (i+1).ToString()+"-й рес.";
                jobresHeader.Rows[0].Cells[i].Value = (i+1).ToString()+"-й рес.";
                InitializeChart1(i);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // Инициализируем диаграммы пустыми значениями
            InitializeEmptyCharts();
            jobs.Clear();
            int[] resources = new int[(int)rescount.Value];
            for (int i = 0; i < jobcount.Value; i++)
            {
                for (int j = 0; j < rescount.Value; j++)
                {
                    resources[j] = 0;
                    resources[j] = Convert.ToInt16(jobres.Rows[i].Cells[j].Value);
                }
                Job job1 = new Job(i, Convert.ToInt16(job.Rows[i].Cells[0].Value), Convert.ToInt16(job.Rows[i].Cells[1].Value), Convert.ToInt16(job.Rows[i].Cells[2].Value), resources, (int)rescount.Value);
                jobs.Add(job1);
                job1 = null;
            }
            SetTimes(jobs);
            for (int i = 0; i < res_Label.RowCount; i++)
            {
                InitializeChart1(i);
            }
            DisplayInitialState(jobs);
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            using (SaveFileDialog saveFileDialog = new SaveFileDialog())
            {
                saveFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                if (saveFileDialog.ShowDialog() == DialogResult.OK)
                {
                    SaveToFile(saveFileDialog.FileName);
                }
            }
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    LoadFromFile(openFileDialog.FileName);
                }
            }
        }
        private void SaveToFile(string filePath)
        {
            using (StreamWriter writer = new StreamWriter(filePath))
            {
                writer.WriteLine(jobcount.Value.ToString());
                writer.WriteLine(rescount.Value.ToString());
                writer.WriteLine(MaximumTime.Value.ToString());
                // Сохраняем ресурсы
                for (int i = 0; i < rescount.Value; i++)
                {
                    writer.WriteLine($"{res.Rows[i].Cells[0].Value}");
                }
                writer.WriteLine(); // Разделитель между ресурсами и работами

                // Сохраняем работы
                for (int i = 0; i < jobcount.Value; i++)
                {
                    string resourceConsumption = string.Join(" ", Enumerable.Range(0, (int)rescount.Value).Select(j =>
                        Convert.ToInt16(jobres.Rows[i].Cells[j].Value)));
                    writer.WriteLine($"{job.Rows[i].Cells[0].Value} {job.Rows[i].Cells[1].Value} {job.Rows[i].Cells[2].Value} {resourceConsumption}");
                }
            }
        }

        private void LoadFromFile(string filePath)
        {
            using (StreamReader reader = new StreamReader(filePath))
            {
                jobcount.Value = Convert.ToInt32(reader.ReadLine());
                rescount.Value = Convert.ToInt32(reader.ReadLine());
                MaximumTime.Value = Convert.ToInt32(reader.ReadLine());
                // Считываем ресурсы
                for (int i = 0; i < rescount.Value; i++)
                {
                    string[] parts = reader.ReadLine().Split(' ');
                    res.Rows[i].Cells[0].Value = parts[0]; // Поступление
                }
                reader.ReadLine(); // Пропустим разделитель между ресурсами и работами

                // Считываем работы
                for (int i = 0; i < jobcount.Value; i++)
                {
                    string[] parts = reader.ReadLine().Split(' ');
                    job.Rows[i].Cells[0].Value = parts[0]; // Начальное событие
                    job.Rows[i].Cells[1].Value = parts[1]; // Конечное событие
                    job.Rows[i].Cells[2].Value = parts[2]; // Длительность
                    for (int j = 0; j < rescount.Value; j++)
                    {
                        string resourceConsumption = parts[3 + j];
                        jobres.Rows[i].Cells[j].Value = resourceConsumption; // Потребление ресурсов
                    }
                }
            }
        }


        private void PlanJobs()
        {
            InitializeEmptyCharts(); // Сбросить графики
            int EndTime = 0;

            // Считываем начальные данные о ресурсах
            int[] resourcesAvailable = new int[(int)rescount.Value];
            int[] resourcePriority = new int[(int)rescount.Value]; // Вектор приоритетов

            for (int i = 0; i < rescount.Value; i++)
            {
                resourcesAvailable[i] = Convert.ToInt16(res.Rows[i].Cells[0].Value); // Изначальное количество ресурсов
                resourcePriority[i] = Convert.ToInt16(res.Rows[i].Cells[1].Value); // Приоритет ресурса (0 или 1)
            }

            // Считываем работы и их ресурсы
            var jobList = new List<Job>();
            for (int i = 0; i < jobcount.Value; i++)
            {
                int[] resourceConsumption = new int[(int)rescount.Value];
                for (int j = 0; j < rescount.Value; j++)
                {
                    resourceConsumption[j] = Convert.ToInt16(jobres.Rows[i].Cells[j].Value);
                }
                jobList.Add(new Job(i, Convert.ToInt32(job.Rows[i].Cells[0].Value),
                                     Convert.ToInt32(job.Rows[i].Cells[1].Value),
                                     Convert.ToInt32(job.Rows[i].Cells[2].Value),
                                     resourceConsumption,
                                     (int)rescount.Value));
            }
            SetTimes(jobList);

            // Создаем начальный план работ
            foreach (var job in jobList)
            {
                PlanJob(job); // Сначала планируем все работы сразу, без учета ресурсов
            }

            // Запускаем окрашивание по времени
            int iter = 0;
            int currentTime = 0;
            while (currentTime < MaximumTime.Value)
            {
                iter++;
                // Проверяем максимальное потребление ресурсов
                var ResourceConsumption = new int[resourcesAvailable.Length];
                for (int i = 0; i < ResourceConsumption.Length; i++)
                {
                    ResourceConsumption[i] = 0;
                }
                foreach (var job in jobList)
                {
                    if (job.StartTime <= currentTime && currentTime < job.StartTime + job.Duration)
                    {
                        for (int i = 0; i < ResourceConsumption.Length; i++)
                        {
                            ResourceConsumption[i] += job.ResourceConsumption[i];
                        }
                    }
                }
                for (int i = 0; i < ResourceConsumption.Length; i++)
                {
                    AddToChart(i, 1, currentTime, resourcesAvailable[i]);
                    AddToChart(i, 2, currentTime, ResourceConsumption[i]);
                }

                // Находим максимальное потребление
                bool canContinue = true;
                for (int i = 0; i < resourcesAvailable.Length; i++)
                {
                    if (ResourceConsumption[i] > resourcesAvailable[i])
                    {
                        canContinue = false;
                        break;
                    }
                }
                if (canContinue)
                {
                    currentTime++;
                }
                else
                {
                    // Вытаскиваем ресурс с наибольшим потреблением среди приоритетных
                    int maxIndex = -1;
                    int maxValue = 0;
                    for (int i = 0; i < ResourceConsumption.Length; i++)
                    {
                        if (resourcePriority[i] == 1 && ResourceConsumption[i] > maxValue)
                        {
                            maxValue = ResourceConsumption[i];
                            maxIndex = i;
                        }
                    }

                    // Если нет приоритетных ресурсов, выбираем любой с максимальным потреблением
                    if (maxIndex == -1)
                    {
                        maxIndex = 0;
                        maxValue = ResourceConsumption[0];
                        for (int i = 1; i < ResourceConsumption.Length; i++)
                        {
                            if (ResourceConsumption[i] > maxValue)
                            {
                                maxValue = ResourceConsumption[i];
                                maxIndex = i;
                            }
                        }
                    }

                    List<Job> busyJobs = new List<Job>();
                    // Ищем работу, которую нужно отложить
                    for (int i = 0; i < jobcount.Value; i++)
                    {
                        if (jobList[i].StartTime <= currentTime && currentTime < jobList[i].StartTime + jobList[i].Duration)
                            busyJobs.Add(jobList[i]);
                    }
                    if (busyJobs.Count > 0)
                    {
                        Job jobToDelay = null;
                        maxValue = 0;
                        foreach (var job in busyJobs)
                        {
                            if (job.ResourceConsumption[maxIndex] > maxValue)
                            {
                                maxValue = job.ResourceConsumption[maxIndex];
                            }
                        }
                        // Выбираем работу с наибольшим потреблением ресурса
                        foreach (var job in busyJobs)
                        {
                            if (job.ResourceConsumption[maxIndex] == maxValue)
                            {
                                jobToDelay = job;
                                break;
                            }
                        }

                        if (jobToDelay != null)
                        {
                            // Сдвигаем эту работу
                            DelayJob(jobList, jobToDelay, resourcesAvailable, currentTime);
                        }

                        foreach (var job in jobList)
                        {
                            if (job.EndTime > EndTime)
                            {
                                EndTime = job.EndTime;
                            }
                        }
                        if (EndTime >= MaximumTime.Value)
                        {
                            break;
                        }
                    }
                }
            }
            jobs = jobList;
            for (int i = 0; i < res_Label.RowCount; i++)
            {
                InitializeChart1(i);
            }
            DisplayInitialState(jobList);
            // После окончания планирования показываем итоговое состояние
        }

        private void DelayJob(List<Job> jobs, Job job, int[] resourcesAvailable, int currentTime)
        {
            foreach (var job1 in jobs)
            {
                if (job.Id == job1.Id)
                {
                    // Выдвигаем работу на 1 временной шаг вправо
                    job1.StartTime += 1;
                }
            }
            SetTimesById(jobs, job.Id);
            foreach (var job1 in jobs)
            {
                chartGantt.Series["GanttSeries"].Points.Clear();
                PlanJob(job1); // Сначала планируем все работы сразу, без учета ресурсов
            }

            // Обновляем графики и журнал
            }

        private void PlanJob(Job job)
        {

            // Добавляем на график Ганта
            chartGantt.Series["GanttSeries"].Points.AddXY(job.Id, job.StartTime, job.StartTime + job.Duration);

            // Обновление графиков по ресурсам
        }

        // Обновляем событие кнопки для запуска планирования
        private void btnPlanJobs_Click(object sender, EventArgs e)
        {
            PlanJobs(); // Вызываем метод планирования
        }

        private void SetTimes(List<Job> jobs)
        {
            for (int i = 0; i < jobs.Count; i++)
            {
                if (jobs[i].StartEvent == 0)
                {
                    jobs[i].EndTime = jobs[i].StartTime + jobs[i].Duration;
                }
                else
                {
                    for (int j = 0; j < jobs.Count; j++)
                    {
                        if (jobs[i].StartEvent == jobs[j].EndEvent)
                        {
                            jobs[i].StartTime = jobs[j].EndTime;
                            jobs[i].EndTime = jobs[i].StartTime + jobs[i].Duration;
                        }
                    }
                }
            }
        }
        private void SetTimesById(List<Job> jobs, int id)
        {
            for (int i = 0; i < jobs.Count; i++)
            {
                if (jobs[i].Id == id)
                {
                    jobs[i].EndTime = jobs[i].StartTime + jobs[i].Duration;
                }
                else
                {
                    for (int j = id; j < jobs.Count; j++)
                    {
                        if (jobs[i].StartEvent == jobs[j].EndEvent)
                        {
                            jobs[i].StartTime = jobs[j].EndTime;
                            jobs[i].EndTime = jobs[i].StartTime + jobs[i].Duration;
                        }
                    }
                }
            }
        }

        public class Job
        {
            public int Id { get; set; }
            public int StartEvent { get; set; }
            public int EndEvent { get; set; }
            public int Duration { get; set; }
            public int[] ResourceConsumption { get; set; }
            public int ResCount;
            public int StartTime { get; set; }
            public int EndTime { get; set; }

            public Job(int id, int startEvent, int endEvent, int duration, int[] resourceConsumption, int Rc)
            {
                Id = id;
                StartEvent = startEvent;
                EndEvent = endEvent;
                Duration = duration;
                ResourceConsumption = new int[Rc];
                for (int i = 0; i < Rc; i++)
                {
                    ResourceConsumption[i] = resourceConsumption[i];
                }
                ResCount = Rc;
                StartTime = 0;
                EndTime = 0;
            }

            public override string ToString()
            {
                string res = "";
                for (int i = 0; i< ResCount; i++)
                {
                    res+= "r"+(i+1).ToString()+": "+ ResourceConsumption[i]+"; ";
                }
                return $"Работа №{Id+1}: Начальное событие = {StartEvent}, Конечное событие = {EndEvent}, продолжительность = {Duration}, Потребление ресурсов = {res}";
            }
        }
    }
}
