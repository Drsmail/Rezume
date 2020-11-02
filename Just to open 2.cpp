// OP 8 A2-B2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;


struct worker
{
public:

    string famil;
    int gpost;
    int grozd;

    worker* next, * prev;

};


struct Data
{
public:

    worker* search = &base;

    void plus();

    worker* find(string name);

    void freeWrite(string famil, int gpost, int grozd);


    // конструктор, вызываеться один раз при создании

    Data()
    {
        // используеться, чтобы инициализировать значения некоторых переменых перед началом работы,
        // выделить первую память, провести расчёты неообходимые для создания структуры и тд.

    }



    // Конструктор копирования
    Data(const Data& org)
    {
        worker* search; const worker* p;

        search = &this->base;    // установим указатель сёрч, на начало структуры, которая вызвала функцию
        p = &org.base;    // тоже самое, но оргумент, содержит в себе всё информацию из него мы будем копировать.


        while ((search->next != NULL) && (p->next != NULL))     // есть что копировать и есть куда копировать
        {
            search = search->next;
            p = p->next;

            search->famil = p->famil;
            search->gpost = p->gpost;
            search->grozd = p->grozd;

        }

        if ((search->next == NULL) && (p->next != NULL))        //  Есть что копировать, но нет куда копировать
        {
            while (p->next != NULL)                          // По сути нужен только этот вайл, так как это конструктор копии, но мне страшно убирать всё остальное.
            {
                this->plus();
                p = p->next;

                this->lead->famil = p->famil;
                this->lead->gpost = p->gpost;
                this->lead->grozd = p->grozd;

            }


        }
        else
        {

            if ((search->next != NULL) && (p->next == NULL))     // Есть куда копировать, но нету то чего копируем (Удаляемм лишнее)
            {

                worker* temp;

                while (search != this->lead)
                {
                    temp = lead->prev;

                    delete lead;

                    lead = temp;

                }


            }

        }



    }

    // Деструктор
    ~Data()
    {

        // cout << "PEREXVAT!!!" << endl;   для отладки

        worker* search = lead, * temp;

        while (search != &base)
        {
            temp = search->prev;

            delete search;

            search = temp;

        }


    }


    Data operator=(const Data& org)   // x = 5 (изсеняеться только левая часть), поэтому аргумен имеет модификатор const, на случай если мы случайно его изменим.
    {                                 // &org Чтобы не вызывать лишний раз, консруктор копии. Так как мы можем работать с оригиналом, и не бояться его сломать
        worker* search; const worker* p;

        search = &this->base;
        p = &org.base;


        while ((search->next != NULL) && (p->next != NULL))
        {
            search = search->next;
            p = p->next;

            search->famil = p->famil;
            search->gpost = p->gpost;
            search->grozd = p->grozd;

        }

        if ((search->next == NULL) && (p->next != NULL))
        {
            while (p->next != NULL)
            {
                this->plus();
                p = p->next;

                this->lead->famil = p->famil;
                this->lead->gpost = p->gpost;
                this->lead->grozd = p->grozd;

            }


        }
        else
        {

            if ((search->next != NULL) && (p->next == NULL))
            {

                worker* temp;

                while (search != this->lead)
                {
                    temp = lead->prev;

                    delete lead;

                    lead = temp;

                }


            }

        }



        return *this;

    }

private:
    worker* lead = &base;
    worker base = { "base",666,666 };   // Первый элемент структуры (основа).
};

void Data::plus()
{
    worker* p = new worker;   //Выделяем память под нового рабочего

    lead->next = p;   // Связали лида с новым челом
    p->prev = lead;   // Связали Нового чела с лидом
    p->next = NULL;   // Поставили конец списка
    lead = p;         // нового чела сделали лидом
}

worker* Data::find(string name)
{
    worker* search = &base;     //Начинаем поиск с бейса

    while (search != NULL)      // Это конец списка?
    {
        if (search->famil == name)
            return search;  // нашли человека

        search = search->next;  // Переход в следующий элимент списка

    }

    return NULL;   // Мы не нашли человека, значит аткого нет


}

void Data::freeWrite(string famil, int gpost, int grozd)
{

    worker* search = &base;                                // Начинаем поиск с бейса  // Плохая идея, лучше начинать с конца, перепишите кто-нибудь

    while ((search != NULL) && (search->famil != ""))       // Ячейка с именем пустая?   либо конец списка
    {
        search = search->next;                             // Переход в следующий элимент списка

    }

    if (search == NULL)
    {
        // cледовательно свободных ячеек нету
        plus();                      // Новая ячейка
        lead->famil = famil;         // Lead тепереь стоит на только что созданной ячейки
        lead->gpost = gpost;         // и мы можем её заполнить
        lead->grozd = grozd;
    }
    else
    {
        search->famil = famil;       // Заполняем найденную пустую ячейку
        search->gpost = gpost;
        search->grozd = grozd;


    }




}

int compare(const void* a, const void* b)
{
    return (2020 - static_cast<const worker*>(a)->grozd) - (2020 - static_cast<const worker*>(b)->grozd);
}


int main()
{

    Data sklad;


    sklad.plus();

    sklad.plus();

    sklad.plus();

    sklad.freeWrite("Maks", 2002, 1986);
    sklad.freeWrite("Vova", 2000, 1973);
    sklad.freeWrite("Bobr", 2013, 2000);
    sklad.freeWrite("Komar", 2020, 1979);


    //show(sklad);

    {
        Data test;

        test = sklad;

    }  // диструктор работает правильно


    worker* search = sklad.search;

    cout << "Part A" << endl;

    while (search != NULL)            ///     A part
    {
        if ((search->grozd <= 1980) && (search->grozd > 1000))
        {
            cout << "Name: " << search->famil << endl;
            cout << "Year of birth: " << search->grozd << endl;
            cout << "Year of receipt: " << search->gpost << endl;
            cout << endl;
        }

        search = search->next;
    }                                 ///     B part

    cout << "Part B" << endl;

    const int N = 2;

    worker Temp[N];
    int count = 0;

    search = sklad.search;

    while (search != NULL)
    {
        if (search->grozd >= 1985)
        {
            Temp[count] = *search;
            count++;
        }

        search = search->next;
    }

    qsort(Temp, count, sizeof(worker), compare);


    search = &Temp[0];

    for (int i = 0; i < count; i++)            ///     A part
    {
        search = &Temp[i];
        cout << "Name: " << search->famil << endl;
        cout << "Year of birth: " << search->grozd << endl;
        cout << "Year of receipt: " << search->gpost << endl;
        cout << endl;


    }                                 ///     B part


    /*
    cout << sklad.find("Maks") << endl;
    cout << sklad.find("Komar") << endl;
    cout << sklad.find("Saha") << endl;
    */

    return 0;
}
