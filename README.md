# Formalki_Practicum1
Практикум по формалкам 1-ый: поиск наибольшего подслова, являющегося подсловом слова в языке

Раскин Иван Б05-923, вариант 16.
Задача: Поиск длины самого длинного подслова u, являющегося также подсловом некоторого слова в L.

BOOLMATRIX
Вспомогательная структура - BoolMatrix - булевая матрица. Заполнена 0 и 1.
Перемножение матриц: M = M1 * M2. M[i][j] == 1, если существует k, такое что M1[i][k] = M2[k][j] = 1;
Сложность - O(Length(U)^3)
Сложение матриц: M = M1 + M2. M[i][j] == 1, M1[i][j] == 1 или M2[i][j] = 1;
Сложность - O(Length(U)^2) 

DYNAMICSTATE
Вспомогательная структура DynamicState(от подстроки U) - характеристика некоторого формального выражения.
Хранит для каждой подстроки U четыре характеристики:
1)Является ли она словом, задаюдающимся данным формальным выражением
2)Является ли она суффиксом слова, задаюдающимся данным формальным выражением
3)Является ли она префиксом слова, задаюдающимся данным формальным выражением
3)Является ли она подсловом слова, задаюдающимся данным формальным выражением
Для этого используются 4 булевые матрицы: Whole, Suffix, Prefix и Middle.
Например, Suffix[i][j] хранит 1, если подслово U[i, j) (используем полуинтервал) является суффиксом
некоторого слова, задающимся данным формальным выражением. 
Диагональ матрицы заполнена единицами т.и т.т., когда пустое слово удовлетворяет требованиям данной матрицы.
Соответственно, если язык - это буква, то Whole заполнена нулями по диагонали, а все остальные матрици единицами.

Когда мы хотим вычислить DynamicStateResult от двух других формальных выражений, связанных некоторой операцией,
берем их DynamicState1 и DynamicState2, и по формулам пересчитываем значения для матриц DynamicStateResult.

Для сложения двух форм.выражений матрицы DynamicState1 и DynamicState2 просто складываются - это очевидно.

Для умножения посложнее, но тоже всё наглядно:
result.Whole = Whole1 * Whole2; - подслово U лежит в результирующем языке, если некоторый его префикс
лежит в первом языке, а оставшийся суффикс во втором
result.Prefix = Whole1 * Prefix2 + Prefix1; - подслово U лежит в префиксе слова результирующего языка,
если его префикс полностью лежит в слове первого языка, а оставшийся суффикс в слове 2-го языка,
либо все подслово лежит в префиксе первого языка.
result.Suffix = Suffix1 * Whole2 + Suffix2;
result.Middle = Suffix1 * Prefix2 + Middle1 + Middle2; - подслово U лежит в послове слова результирующего языка,
если оно является подсловом слова в одном из языков, либо некоторый его префикс - суффикс слова в первом языке,
а оставшийся суффикс - префикс слова во втором языке
Максимальная сложность операции - O(Length(U)^3) 

Аналогично просто выводятся формулы для вычисления DynamicStateResult от звезды Клини некоторого формального выражения. Единственно что, для вычисления result.Whole необходимо вычислить замыкание 
графа, заданного исходной матрицей Whole, так как при возведении матрицы в квадрат, по сути, для графа, заданного данной матрицей смежностей,мы ищем замыкание дальности 1(для каждой вершины i делаем соседниими те, до которых от i можно дойти не более чем по двум ребрам. Соответсвенно, при сложении всех степеней Whole получаем полное замыкание графа.
Cложность замыкания - O(Length(U)^3) 

РЕШЕНИЕ ЗАДАЧИ
Использую динамику по разбору формального выражения.
Когда читаю букву, кладу в стек DynamicState от неё. Когда читаю опреацию, достаю нужное количество
DynamicState. Применяю к ним соответствующую операцию и кладу результат обратно в стек.
Если в конце программы в стеке лежит только один DYNAMICSTATE, то всё хорошо: достаю его и
узнаю длину самого длинного подслова u, являющегося также подсловом некоторого слова в L,
выбирая максимальный по длине отрезок в матрице Middle. Его длина - это ответ.
Сложность решения задачи по времени: O(Length(L)*Length(U)^3)