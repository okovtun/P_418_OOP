https://github.com/okovtun/P_418_OOP.git
https://www.youtube.com/playlist?list=PLeqyOOqxeiINv7LnwWzt8C-7a8kMKYRp9

Венгерская нотация:
https://ru.wikipedia.org/wiki/%D0%92%D0%B5%D0%BD%D0%B3%D0%B5%D1%80%D1%81%D0%BA%D0%B0%D1%8F_%D0%BD%D0%BE%D1%82%D0%B0%D1%86%D0%B8%D1%8F

TODO:
1. Из файла '201 RAW.txt' создать файл '201 WOL.txt',				DONE
   в котором столбцы с IP-адресом и MAC-адресом поменяны местами;
	https://github.com/okovtun/P_418_OOP/blob/master/Inheritance/WOL/201%20RAW.txt
2. Из файла '201 RAW.txt' создать файл '201.dhcpd', который должен вынлядеть	DONE
   следующим образом:
	https://github.com/okovtun/P_418_OOP/blob/master/Inheritance/Task/201.dhcpd.txt
3. В проекте 'Academy' сохранить группу в файл;
4. В проекте 'Academy' загрузить группу из файла;

DONE:
1. Выучить теорию по наследованию.
2. Написать класс 'Graduate', описывающий дипломника;
3. Участники группы должны выводиться на экран при помощи 'cout':
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		//group[i]->info();
		cout << *group[i] << endl;
	}

DONE:
1. Написать и проветрить MoveAssignment;
2. Почитать:
	https://legacy.cplusplus.com/doc/tutorial/classes2/
3. Почитать:
	https://learn.microsoft.com/en-us/cpp/build/reference/zc-nrvo?view=msvc-170

DONE:
1. В классе 'String' написать и проверить CopyAssignment;		DONE
2. Код в секции 'OPERATORS_CHECK' должен заработать:
	https://github.com/okovtun/P_418_OOP/blob/f69e273b959b37156fc4c1e8fdf5910f6f74a339/IntroductionToOOP/String/main.cpp#L82C1-L87C26

DONE:
0. !!!!!!! ПОВТОРИТЬ ПРИМИТИВНЫЕ ТИПЫ ДАННЫХ C++ !!!!!!!
1. Почитать про Венгерскую нотацию:
	https://ru.wikipedia.org/wiki/%D0%92%D0%B5%D0%BD%D0%B3%D0%B5%D1%80%D1%81%D0%BA%D0%B0%D1%8F_%D0%BD%D0%BE%D1%82%D0%B0%D1%86%D0%B8%D1%8F
2. Написа функцию isIPaddressTok() используя функцию strtok():
	https://legacy.cplusplus.com/reference/cstring/strtok/
3. В Solution 'IntroductionToOOP' добавить проект 'String',
   и в этом проекте реализовать класс 'String', который описывает строку.
	Строка - это самый обычный массив элементов char, 
	последним элементом корого всегда является ASCII-символ с кодом 0 - '\0',
	который представляет собой самый обычный физический 0.

DONE:
В Solution 'IntroductionToOOP' добавить проект 'NULLTerminatedLines',
и перенести в него весь код из проекта 'String';

DONE:
Реализовать следующие функции:
	??? StringLength(???);	//возвращает длину строки				DONE
	??? ToUpper(???);		//переводит строку в верхний регистр	DONE
	??? ToLower(???);		//переводит строку в нижний регистр		DONE

	void shrink(???);		//Удаляет лишние пробелы из предложения	DONE
							//Хорошо      живет     на     свете      Винни      Пух
							//Хорошо живет на свете Винни Пух

	??? is_palindrome(???);	//Проверяет, является ли строка палиндромом	DONE

	??? is_int_number(???);	//Проверяет, является ли строка целым десятичным числом
	??? to_int_number(???); //Если строка является целым десятичным числом, возвращает ее числовое значение		
	??? is_bin_number(???);	//Проверяет, является ли строка двоичным числом		
	??? bin_to_dec(????);	//Если строка является двоичным числом, возвращает ее десятичное значение			
	??? is_hex_number(???);	//Проверяет, является ли строка шестнадцатеричным числом							
	??? hex_to_dec(???);	//Если строка является шестнадцатеричным числом, возвращает ее десятичное значение	
	--------------------------------------
	??? isIPaddress(???);	//Проверяет, является ли строка IP-адресом		
	??? isMACaddress(???);	//Проверяет, является ли строка MAC-адресом

TODO:
1. !!!!!	ТЕОРИЮ НАИЗУСТЬ		!!!!!
2. Проверочный код в секции HOME_WORK должен заработать:
	https://github.com/okovtun/P_418_OOP/blob/02559b9addbf69d1a47406ee655b41d851f16387/IntroductionToOOP/Fraction/main.cpp#L430C1-L433C20

DONE:
1. !!!!!	ТЕОРИЮ НАИЗУСТЬ		!!!!!
2. ***Решить проблему в операторе '*';
3. Перегрузить составные присваивания: +=, -=, *=, /=;
4. Перегрузить декременты;
5. Перегрузить операторы сравнения;
6. Проверочный код дожен заработать:
	Fraction A;
	cout << "Введите простую дробь: "; cin >> A;
	cout << A << endl;

DONE:
1. !!!!!	ТЕОРИЮ НАИЗУСТЬ		!!!!!
2. В Solution 'IntroductionToOOP' добавить проект 'Fraction', описывающий простую дробь.
   В классе должны быть все необходимые методы и операторы;

DONE:
1. !!!!!	ТЕОРИЮ НАИЗУСТЬ		!!!!!
2. Исправить ошибки в секции 'ASSIGNMENT_CHECK';

DONE:
1. !!!!!	ТЕОРИЮ НАИЗУСТЬ		!!!!!
2. Написать метод ??? distance(???), который находит расстояние до указанной точки;		DONE
3. Написать функцию ??? distance(???), которая находит расстояние между двумя точками;	DONE
4. Повторить параметры по умолчанию;
5. Повторить передачу параметров;