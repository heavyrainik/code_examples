 В качестве основы я выбрал паттерн - абстрактная фабрика. У меня имеются
 4 класса "продуктов", отнаследованные от абстрактного класса Unit:
 пехота, кавалерия, маги и особые юниты. Абстрактный класс фабрики UnitFactory,
 у которого есть абстрактный метод set_hp и обычный метод draw, далее от него
 наследуются классы HumanFactory, OrkFactory, ElfFactory и DemonFactory.
 Каждая из этих фабрик возвращает пехоту, кавалерия, мага или специальный юнит
 своей расы, которые являются наследниками классов "продуктов". Таким образом
 схема моего создания новых юнитов выглядит примерно как на этом сайте в разделе
 структура https://refactoring.guru/ru/design-patterns/abstract-factory .
 
 Касательно тестов, их нет, ну точнее есть мой маленький, рукописный тест, который
 просто создает каждого юнита, которого может и отрисовывает его на экране - я сделал
 небольшой графический интерфейс, чтобы проверить, правильно ли работают функции.
 Оказвается, правильно, потомуу что у каждого юнита, кроме специальных, которые
 являются частью лора и которых надо продумать, имеют свои уникальные модельки,
 и они отображаются на экране.
 
 Для запуска надо склонировать проект к себе и запустить через IDE, не проверял,
 запуститься ли на любой, но на Pycharm 100%