# Л/р по дисциплине "Алгоримты и структуры данных". Осень 2019
## Таблица сдачи и приема работ студентов - группа 8304

| №| Фамилия Имя |  lab1  |  lab2   |  lab3   |  lab4   |  lab5   |course_work| Summary |
| -|:------------|:-------:|:-------:|:-------:|:-------:|:-------:|:---------:|:---------:|
| 1| Алтухов Александр | 5.5 | 6 | 7 | 6 | 6 | отл | 29 |
| 2| Барышев Андрей | 4 | 4 | 4 | 5 | 6 | отл | 23 |
| 3| Бутко Артем | 5 | 4.5 | 7 | 5.5 | 7 | отл | 28 |
| 4| Бочаров Филлип | 0 | 4 | 4 | 4 | | | |
| 5| Воропаев Антон | 5 | 6 | 6 | 7 | 7 | отл | 30 |
| 6| Завражин Дмитрий | 5 | 5 | | | | | |
| 7| Ивченко Антон | 3.5 | 4 | 3.5 | 4 | 6 | отл | 22 |
| 8| Карабанов Роман | 3 | 4 | 4 | | | | |
| 9| Кирьянов Даниил | 5 | 4 | 6 | 4 | 6 | хор- | 24(п)! |
|10| Масалыкин Даниил | 4 | 4 | 4 | | | | |
|11| Матросов Денис | 4 | | | | | | |
|12| Мельникова Ольга | 6 | 6 | 5.5 | 6 | 6 | отл | 29 |
|13| Мешков Максим | 6 | 5.5 | 6 | 7 | 7 | отл | 30 |
|14| Мухин Александр | 5 | 6 | 6 | 6 | 7 | отл | 29 |
|15| Нам Е Себ | 4 | 4 | | | | | |
|16| Николаева Мария | 5 | 6 | 6 | 6 | 6 | отл | 28 |
|17| Порывай Павел | 3.5 | 3 | 6 | 6 | 5 | удовл | 22(п) |
|18| Птухов Денис | 5 | 7 | 7 | 7 | 7 | отл | 30 |
|19| Рыжиков Александр | 6 | 6 | 6 | 5 | 7 | отл | 29 |
|20| Самакаев Дмитрий | 4 | 5.5 | 5.5 | 4 | | | |
|21| Сани Заяд | 4 | 5.5 | 6 | 5.5 | 6 | | |
|22| Холковский Константин | 6 | 6 | 7 | 7 | 7 | отл | 30 |
|23| Чечеткина Ксения | 0 | | | | | | |
|24| Чешуин Дмитрий | 6 | 6 | 6 | 4 | 4 | | |
|25| Щука Александр | 6 | 7 | 7 | 7 | 7 | отл | 30 |
|26| Ястребов Иван | 6 | 4 | 6 | 6 | 6 | | |

(п) - предварительно. После 27.12 превратится в окончательную.

### Критерии выставления оценок деятельности за семестр
За лабораторные работы можно получить максимум 31 балл. 

За курсовую работу можно получить максимум 5 баллов.

**Итого:** максимально 36 баллов можно получить, сдав все работы.
Конечный балл за семестр получается умножением полученных баллов за работы на коэффициент 5/6.

### Дедлайны
| № работы |  мягкий | жесткий |
|:--------:|:-------:|:-------:|
|   Лаб 1  |    -    |  24.09  |
|   Лаб 2  |  24.09  |  16.10  |
|   Лаб 3  |  16.10  |  05.11  |
|   Лаб 4  |  05.11  |  27.11  |
|   Лаб 5  |  27.11  |  11.12  |

## Правила работы с репозиторием

- Для начала работы нужно сделать форк этого репозитория и скопировать его себе на компьютер
- Для каждой лабораторной создается **своя отдельная ветка** c названием в формате <Surname\lab#>
- Работать следует строго в своей директории Surname/
- Для каждой работы создаётся отдельная директория lab#, где # - номер лабораторной
- Курсовая работа заливается в директрию course_work
- При внесении локальных изменений следует работать со своим форком репозитория

- Внутри папки с названием должны находиться:
    * Исходный код программ в папке Source
    * Тестовые данные в папке Tests
    * makefile или скрипт командной строки для получения исполняемого файла с названием lab# в корневой папке
    * скрипт командной строки или на Python для возможности запуска всех тестов из папки Tests одной командой
    * отчёт (строго в формате pdf)
- Внутри папки с названием не должны находиться:
    * файлы с выводом программы
    * исполняемые файлы
    * аниме-картинки и другие изображения
    * всё остальное
    
## Алгоритм сдачи работ
- Для проверки лабораторной работы следуте создать pull-request из своей ветки с лабораторной работой в master-ветку общего репозитория. Заголовок пул-реквеста следует оформлять в формате <lab# - Фамилия>
- В описании к пулл-реквесту дописать **номер выбранного варианта**
- В ходе проверки в названии PR могут появиться 4 квадратные скобочки со статусами сдачи частей работы (об этом ниже)
- Что означают квадратные скобочки по порядку:
  - Первая - код (0-2 плюсика после защиты)
  - Вторая - тесты (0-1 плюсик после защиты)
  - Третья - отчёт (0-1 плюсик после защиты)
  - Что означают статусы в квадратных скобочках при заочной проверке?
  - [FIX] - требуются изменения
  - [FIXED] - исправлено, можно проверять
  - [ACCEPT] - принято к очной сдаче
- При сдаче до мягкого дедлайна можно дополнительно получить ещё один плюсик
- Про пропуске жёсткого дедлайна автоматически теряется 2 плюсика за работу
- За одну работу можно получить до 7 плюсиков, за весь семестр - 30
- Темы и оценка курсовой будут позже

- **Работа считается зачтённой, если во всех скобках есть хотя бы один плюсик**

- **Напоминания:** 
  - Коммиты с исправлениям отображаются в самом пул-реквесте. **Делать новый пул-реквест для исправлений не надо**
  - Закончив исправления, нужно **самому** изменить статус в соответсвующей части заголовка на [FIXED]

## Требования к работам
### По коду
Главные требования: единый стиль именования переменных и аккуратная работа с памятью. 

Будет плюсом: использование возможностей современного С++, принципов RAII и SOLID.

### По тестам
Тесты должны покрывать разнообразные случаи входных данных - 10 однобоких тестов на засчитываются. Структура тестовых данных - на усмотрение разработчика. Также можно сделать сравнение вывода программы с эталонным результатом.
По-хорошему главная программа не должна знать о том, что её тестируют.

### По отчёту
В отчёте обязательно должны быть:
- Задание + вариант работы
- Описание алгоритма работы (+ пояснения)
- Описание основных структур данных и функций (кратко)
- Тестирование: табличка ввод-вывод с тестами выше (в отчёт только основные тесты)
- Вывод + код

## Контакты
По всем вопросам можете писать на почту makometr@yandex.ru. В заголовке письма указвайте префикс [ASD]

