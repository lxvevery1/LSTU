@startuml

skin rose

usecase "Создание заказа" as UC1
usecase "Принятие заказа" as UC6
usecase "Просмотр наборов" as UC2
usecase "Формирование отчета" as UC4
usecase "Обновление данных БД" as UC5

actor "Менеджер" as Manager
actor "Администратор" as Admin

Manager --> UC1 : инициирует
Manager --> UC2 : просматривает
Admin --> UC6 : принимает
Admin --> UC4 : формирует
Admin --> UC5 : обновляет

UC1 --> UC6 : после создания заказа
UC4 --> UC2 : для получения данных

UC6 ..>> UC5 : обновляет статус заказа)

@enduml
