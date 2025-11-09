@startuml

' Определение сущностей
entity "Смотритель" as User {
    + ID : uint
    --
    Имя : string
    Фамилия : string
    Email : string
}

entity "Набор" as Kit {
    + ID : uint
    --
    Номер : string
    Наименование : string
    Статус : string
    МестоХранения : string
    Клиника : string
    Менеджер : string
    ДатаПеремещения : date
    КоличествоДнейВКлинике : uint
    Комментарии : string
    Подразделение : string
}

entity "Фото" as Photo {
    + ID : uint
    --
    Название : string
    Путь : string
}

entity "Акт" as Act {
    + ID : uint
    --
    Название : string
    Путь : string
}

entity "Клиника" as Clinic {
    + ID : uint
    --
    Название : string
    Адрес : string
}

entity "Менеджер ЛПУ" as Manager {
    + ID : uint
    --
    Имя : string
    Фамилия : string
    Email : string
}

entity "ЖурналПеремещений" as MovementLog {
    + ID : uint
    --
    Дата : date
    Откуда : string
    Куда : string
    Комментарий : string
}

' Менеджер посылает запрос на набор администратору (смотрителю)
entity "Запрос" as Request {
  + ID : uint
  --
  Номер_набора : uint
  Состояние_заказа : enum
}

' каждый набор имеет наполнение, которое состоит из фото и акта
entity "Наполнение" as KitFill {
    + ID : uint
    --
    Акт : Act
    Фото : Photo
}

' Определение связей
User ||--o{ Kit : "контролирует состояние"
Kit ||--o{ MovementLog : "имеет"
Kit }o--|| Clinic : "хранится в"
User ||--o{ Kit : "следит за"
User ||--o{ Request : "получает"

' Дополнительные связи
Manager ||--o{ Request : "отправляет"
Request }o--|| Kit : "относится к"
Kit ||--o{ KitFill : "имеет"
KitFill ||--o{ Photo : "содержит"
KitFill ||--o{ Act : "содержит"

@enduml
