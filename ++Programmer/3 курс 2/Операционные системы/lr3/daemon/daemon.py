import time
import random
from plyer import notification
from PIL import Image

def show_images(images):
    for image in images:
        img = Image.open(image)
        img.show()

def eye_rest_demon(repetition_period, relax_time, images):
    while True:
        # Случайный выбор времени для начала отдыха
        start_rest_time = random.randint(1, repetition_period)
        # Случайный выбор времени для продолжительности отдыха
        duration_rest = random.randint(1, relax_time)

        # Ожидание начала отдыха
        time.sleep(start_rest_time)

        # Уведомление о начале отдыха
        notification.notify(
            title="Отдых для глаз",
            message="Пора отдохнуть от экрана! Время отдыха: {} мин.".format(duration_rest),
            timeout=10
        )

        # Показ изображений
        show_images(images)

        # Ожидание окончания отдыха
        time.sleep(duration_rest * 60)

        # Закрытие всех открытых изображений
        Image.close()

        # Уведомление об окончании отдыха
        notification.notify(
            title="Время вернуться к работе",
            message="Отдых закончен. Время вернуться к работе!",
            timeout=10
        )

if __name__ == "__main__":
    repetition_period = 60  # Периодичность проверки, в секундах
    relax_time = 2  # Продолжительность отдыха, в минутах
    images = ["image_1.png", "image_2.jpg", "image_3.jpg", "image_4.jpg", "image_5.jpg"]
    eye_rest_demon(repetition_period, relax_time, images)


