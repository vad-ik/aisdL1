#include <iostream>

using namespace std::chrono;
struct cell {//элемент ячейки списка
    int inf;
    cell* next = NULL;
};
struct myList {//список
    cell* head;//указатель на начало списка
    cell* end;//указатель на конец списка
};

void addInTheEnd(myList& list, int inf) {//добавить элемент в конец

    if (list.end == NULL) {//если список пуст
        cell* cur = new cell{ inf, NULL };//создать элемент
        list.head = cur;//элемент и первый и последний
        list.end = cur;
    }
    else
    {
        cell* cur = new cell{ inf, NULL };//создать элемент
        list.end->next = cur;//добавить элемент в конец
        list.end = cur;//теперь он последний
    }
}
void addInTheStart(myList& list, int inf) {//добавить элемент в начало
    if (list.head == NULL) {//если список пуст
        cell* cur = new cell{ inf, NULL };//создать элемент
        list.head = cur;//элемент и первый и последний
        list.end = cur;
    }
    else
    {
        cell* cur = new cell{ inf, list.head };//создать элемент
        list.head = cur;//теперь он первый
    }
}
int getLength(cell& select) {//найти длину списка
    cell* selected = &select;
    int i = 0;
    while (selected != NULL)
    {
        selected = selected->next;
        i++;
    }
    return i;
}

void delLast(myList& list) {//удалить последний элемент

    if (list.head == NULL) {}//если список пуст удалять нечего
    else if (list.head->next == NULL)//если список состоит из одного элемента
    {
        delete list.head;//удаляем единственный элемент
        list.end = NULL;
    }
    else
    {
        cell* cur = list.head;
        int k = getLength(*list.head);
        for (int i = 0; i < k - 2; i++)//дойти до элемента предшествующий последнему элементу
        {
            cur = cur->next;
        }
        cell* cur2 = cur->next;
        cur->next = NULL;
        list.end = cur;
        delete cur2;//удаляем элемент
    }
}
void delFerst(myList& list) {//удалить первый элемент
    if (list.head == NULL) {}
    else if (list.head->next == NULL)
    {
        list.head = NULL;
        list.end = NULL;
    }
    else
    {
        cell* cur = list.head;
        list.head = list.head->next;
        delete cur;
    }
}
void addI(myList& list, int inf, int i) {//добавить элемент в конец
    if (i == 0)
    {
        addInTheStart(list, inf);//первый элемент добавить в начало
    }
    else
    {
        cell* cur2 = list.head;
        for (int j = 1; j < i && cur2->next != NULL; j++)//подходим к элементу предшествующим вставляемому элементу или к концу списка
        {
            cur2 = cur2->next;
        }
        cell* cur = new cell{ inf, cur2->next };//создать элемент
        cur2->next = cur;//вставить элемент
    }
}
cell* getI(myList& list, int i) {
    if (i > getLength(*(list.head))) {
        std::cout << "индекс больше массива";

    }
    else if (i == 0)
    {
        return list.head;
    }
    else
    {
        cell* cur = list.head;
        for (int j = 1; j < i; j++)
        {
            cur = cur->next;
        }
        return cur->next;
    }
}
void delI(myList& list, int i) {//удалить элемент по индексу
    if (i > getLength(*(list.head))) {//проверка на выход из диапазона
        std::cout << "индекс больше массива";
    }
    else if (i == 0)//удаление первого элемента
    {
        delFerst(list);
    }
    else if (i == getLength(*(list.head)))//удаление последнего элемента
    {
        delLast(list);
    }
    else {
        cell* cur = list.head;
        for (int j = 1; j < i; j++)//дойти до предыдущего элемента перед вставляемым
        {
            cur = cur->next;
        }
        cell* cur2 = cur->next;
        cur->next = cur->next->next;
        delete cur2;//удалить элемент
    }
}
void delAll(myList& list) {//удалить все
    cell* cur = list.head;
    while (list.head != NULL)// пока есть элементы списка
    {
        list.head = list.head->next;
        delete cur;// удалять
        cur = list.head;
    }
    delete list.head;//очистить 
    list.end = NULL;
}
void replacementI(myList& list, int inf, int i) {//заменить элемент на передаваемый
    if (i >= getLength(*(list.head))) {//если идекс больше размера массива
        std::cout << "индекс больше массива, элемент будет добавлен в конец";
        addInTheEnd(list, inf);
    }
    else if (i == 0)//если элемент вставляется на первое место
    {
        addInTheStart(list, inf);//добавить новый элемент в конец
        if (getLength(*list.head) >= 3)// если список был длиннее одного элемента
        {
            cell* cur = list.head->next;
            list.head = list.head->next->next;//указатель на следующий элемент после удаляемого
            delete cur;//удалить предыдущий первый элемент
        }
        else if (getLength(*list.head) == 2)//раньше элемент был один
        {
            list.head->next = NULL;//удаляем предыдущий элемент
            delete list.end;
            list.end = list.head;
        }

    }
    else//заменяется элемент не в начало
    {
        cell* cur = list.head;
        for (int j = 1; j < i; j++)//подходим к элементу предшествующим вставляемому элементу 
        {
            cur = cur->next;
        }
        cell* cur2 = new cell{ inf, (cur->next->next) };//заменить элемент
        if (cur2->next == NULL)
        {
            list.end = cur2;
        }
        delete(cur->next);//удалить предыдущий элемент
        cur->next = cur2;
    }
}
bool chekVoid(myList& list) {//проверка пустой ли список
    if (list.head == NULL)
    {
        return true;
    }
    else {
        return false;
    }
}
void revers(myList& list) {//поменять порядок элементов
    if (getLength(*(list.head)) > 1)
    {
        cell* iter = list.head->next;//следующая ячейка
        cell* cur = list.head;//нынешняя ячейка
        list.end = cur;
        cur->next = NULL;
        cell* teil = list.end;//предыдущая ячейка
        while (iter->next != NULL) {
            cur = iter;//сделать шаг вперед
            iter = iter->next;
            cur->next = teil;//элемент указывает назад
            teil = cur;//подвинуть вперед предыдущую ячейку
        }
        iter->next = teil;
        list.head = iter;
    }
}
void addListId(myList& list, myList& list2, int i) {//добавить второй список в первый по индексу
    if (getLength(*(list2.head)) > 0)//если 2 список не пустой
    {
        if (i >= getLength(*(list.head))) {//добавить в конец
            std::cout << "индекс больше массива, 2 массив будет добавлен в конец";
            list.end->next = list2.head;
            list.end = list2.end;
        }
        else if (i == 0)//добавить в начало
        {
            list2.end->next = list.head;
            list.head = list2.head;
        }
        else// добавить в середину
        {
            cell* cur = list.head;
            for (int j = 1; j < i; j++)//дойти до элемента
            {
                cur = cur->next;
            }
            list2.end->next = cur->next;//вставить список
            cur->next = list2.head;
        }
    }
    list2 = { NULL,NULL };//очистить 2 список

}
void addListStart(myList& list, myList& list2) {
    if (getLength(*(list2.head)) > 0)//если 2 список не пустой
    {
        list2.end->next = list.head;
        list.head = list2.head;
    }
    list2 = { NULL,NULL };//очистить 2 список
}
void addListEnd(myList& list, myList& list2) {
    if (getLength(*(list2.head)) > 0)//если 2 список не пустой
    {  
        list.end->next = list2.head;//вставить список
        list.end = list2.end;
    }
    list2 = { NULL,NULL };//очистить 2 список
}
int chekFerstСollision(cell* listHead, myList list2) {//найти первое всхождение второго списка в первый 
    if (getLength(*list2.head) > 0) {// второй список не пустой
        int i = 0;
        int  memeryСollisionId = NULL;

        cell* cur = listHead;
        cell* cur2 = list2.head;
        while (cur != NULL && cur2 != NULL && memeryСollisionId == NULL)//пока не дойдем до конца любого списка
        {
            if (cur->inf == cur2->inf)//значение равно, переходим к следующему элементу 2 списка
            {
                if (memeryСollisionId == NULL) {//первый элемент 2 списка
                    memeryСollisionId = i;
                }
                cur2 = cur2->next;
            }
            else
            {
                cur2 = list2.head;
                memeryСollisionId = NULL;
            }
            cur = cur->next;
            i++;
        }
        if (memeryСollisionId != NULL)//дошли до конца 2 списка
        {
            return memeryСollisionId;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        std::cout << "второй список пуст\n";
    }
}
bool chhekCollision(myList list, myList list2) {
    int ansver = chekFerstСollision(list.head, list2);
    if (ansver >= 0)
    {
        return true;
    }
    else {
        return false;
    }
}
int chekLastСollision(myList list, myList list2) {//поиск последнего вхождения
    int i = 0;
    int  memeryСollisionId;
    int lastСollisionId = NULL;

    cell* cur = list.head;
    cell* cur2 = list2.head;
    while (cur != NULL)//поиск последнего вхождения, но не проверяет входящиe друг в друга последовательности.
    {
        if (cur->inf == cur2->inf)
        {
            if (memeryСollisionId == NULL) {//первый элемент 2 списка
                memeryСollisionId = i;
            }

            if (cur2->next == NULL)
            {
                lastСollisionId = memeryСollisionId;
                cur2 = list2.head;
                memeryСollisionId = NULL;
            }
            else
            {
                cur2 = cur2->next;
            }
        }
        else
        {
            cur2 = list2.head;
            memeryСollisionId = NULL;
        }
        cur = cur->next;
        i++;
    }
    if (lastСollisionId != NULL) {//если было хоть одно попадание, ищем пересекающиеся вхождения после
        int j = 0;
        for (size_t i = lastСollisionId; i >= 0 && j < getLength(*list2.head); ++i, ++j)
        {
            i = chekFerstСollision(getI(list, i), list2);
            if (i >= 0)
            {
                lastСollisionId = i;
            }
        }
        return lastСollisionId;
    }
    else
    {
        return -1;
    }
}
void swap(myList& list, int id1, int id2) {//поменять элементы местами
    int inf1 = getI(list, id1)->inf;//сохранить информацию
    int inf2 = getI(list, id2)->inf;
    replacementI(list, inf1, id2);//заменить элементы
    replacementI(list, inf2, id1);
}



int main()
{
    cell* iter;
    int comand = 0;
    myList list1 = { NULL,NULL };
    myList list2 = { NULL,NULL };
    bool list1Use = true;


    int i = 0, j = 0;
    setlocale(LC_ALL, "Russian");

    std::cout << "доступные команды, введите номер команды\n";

    std::cout << "1) addInTheEnd - добавляет элемент в конец \n";
    std::cout << "2) addInTheStart - добавляет элемент в начало \n";
    std::cout << "3) delLast - удаляет последний элемент \n";
    std::cout << "4) delFerst - удаляет перывый элемент \n";
    std::cout << "5) getLength - возвращает длину \n";
    std::cout << "6) addI - добавляет элемент по индексу \n";
    std::cout << "7) getI - получить элемент по индексу \n";
    std::cout << "8) delI - удалить элемент по индексу \n";
    std::cout << "9) delAll - удалить весь список \n";
    std::cout << "10) replacementI заменить элемент по индексу  \n";
    std::cout << "11) chekVoid - проверить пустой ли список  \n";
    std::cout << "12) revers - инверсировать список \n";
    std::cout << "13) addListId - вставить второй список по индексу \n";
    std::cout << "14) addListStart - вставить список в начало \n";
    std::cout << "15) addListEnd - вставить список в конец \n";
    std::cout << "16) chekFerstСollision - возвращает id первого вхождения второго списка в первый \n";
    std::cout << "17) chhekCollision - проверить вхождение второго списка в первый \n";
    std::cout << "18) chekLastСollision - возвращает id последнего вхождения второго списка в первый \n";
    std::cout << "19) swap - меняет два элемента местами \n";
    std::cout << "20) nextList - переключится на следующий список (доступно 2) \n";
    std::cout << "21) end - выход из программы \n";
    while (comand != 21)    
    {
        std::cout << "\nвведите номер команды \n";
        std::cin >> comand;
        switch (comand)
        {
        case 1:
            std::cout << "введите число вставляемое в массив\n";
            std::cin >> i;
            if (list1Use)
            {
                addInTheEnd(list1, i);
            }
            else {
                addInTheEnd(list2, i);
            }
            break;
        case 2:
            std::cout << "введите число вставляемое в массив\n";
            std::cin >> i;
            if (list1Use)
            {
                addInTheStart(list1, i);
            }
            else {
                addInTheStart(list2, i);
            }
            break;
        case 3:
            if (list1Use)
            {
                delLast(list1);
            }
            else {
                delLast(list2);
            }
            break;
        case 4:
            if (list1Use)
            {
                delFerst(list1);
            }
            else {
                delFerst(list2);
            }
            break;
        case 5:
            if (list1Use)
            {
                std::cout << getLength(*(list1.head));
            }
            else {
                std::cout << getLength(*(list2.head));
            }
            break;
            std::cout << "\n";
        case 6:
            std::cout << "введите число вставляемое в массив и его индекс\n";
            std::cin >> i >> j;
            if (list1Use)
            {
                addI(list1, i, j);
            }
            else {
                addI(list2, i, j);
            }
            break;
        case 7:
            std::cout << "введите индекс искомого элемента";
            std::cin >> i;
            std::cout << "значение элемента: \n";
            if (list1Use)
            {
                std::cout << getI(list1, i)->inf;
            }
            else {
                std::cout << getI(list2, i)->inf;
            }
            std::cout << "\n";
            break;
        case 8:
            std::cout << "введите индекс удаляемого элемента\n";
            std::cin >> i;
            if (list1Use)
            {
                delI(list1, i);
            }
            else {
                delI(list2, i);
            }
            break;
        case 9:
            if (list1Use)
            {
                delAll(list1);
            }
            else {
                delAll(list2);
            }
            break;
        case 10:
            std::cout << "введите число на которое заменить и его индекс\n";
            std::cin >> i >> j;
            if (list1Use)
            {
                replacementI(list1, i, j);
            }
            else {
                replacementI(list2, i, j);
            }
            break;
        case 11:
            if (list1Use)
            {
                if (chekVoid(list1)) {
                    std::cout << "список пуст \n";
                }
                else { std::cout << "список не пуст \n"; }
            }
            else if (chekVoid(list2)) {
                std::cout << "список пуст \n";
            }
            else {
                std::cout << "список не пуст \n";
            }
            break;
        case 12:
            if (list1Use)
            {
                revers(list1);
            }
            else {
                revers(list2);
            }
            break;
        case 13:
            std::cout << "введите индекс, куда вставить 2 список\n";
            std::cin >> i;
            addListId(list1, list2, i);
            break;
        case 14:
            addListStart(list1, list2);
            break;
        case 15:
            addListEnd(list1, list2);
            break;
        case 16:
            std::cout << "первое попадание начинается на индексе: ";
            std::cout << chekFerstСollision(list1.head, list2);
            std::cout << "\n";
            break;
        case 17:
            if (chhekCollision(list1, list2)) {
                std::cout << "первый список содержит второй\n";
            }
            else {
                std::cout << "первый список не содержит второй\n";
            }
            break;
        case 18:
            std::cout << "последнее попадание начинается на индексе: ";
            std::cout << chekLastСollision(list1, list2);
            std::cout << "\n";
            break;
        case 19:
            std::cout << "введите индексы меняемых элементов\n";
            std::cin >> i >> j;
            if (list1Use)
            {
                swap(list1, i, j);
            }
            else {
                swap(list2, i, j);
            }
            break;
        case 20:
            list1Use = !list1Use;
            if (list1Use) {
                std::cout << "выбран список 1\n";
            }
            else
            {
                std::cout << "выбран список 2\n";
            }
            break;
        }
        std::cout << "список 1 :\n";
        iter = list1.head;
        while (iter != NULL)
        {
            std::cout << iter->inf << " ";
            iter = iter->next;
        }
        std::cout << "\nсписок 2 :\n";
        iter = list2.head;
        while (iter != NULL)
        {
            std::cout << iter->inf << " ";
            iter = iter->next;
        }
    }
}
