// smart_home.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
enum switches
{
LIGHTS_INSIDE = 1,
LIGHTS_OUTSIDE = 2,
HEATERS = 4,
WATER_PIPE_HEATING = 8,
CONDITIONER = 16
};

int  water_pipe(int temperature_outside,int switches_state)      // включение - выключение ОБОГРЕВА ПОМПЫ
{
    if (temperature_outside < 0)                            // если темпер < 0 включаем обогрев помпы 
    {
        switches_state |= WATER_PIPE_HEATING;
    }
    if (temperature_outside > 5)
    {
        switches_state &= ~WATER_PIPE_HEATING;              // если темпер  > 5 отключаем обогрев помпы
    }
    return switches_state;
}
int  weather_in_the_house(int temperature_inside, int switches_state)      // включение - выключение ОТОПЛЕНИЯ И КОНДИЦИОНЕРА
{
    if (temperature_inside < 22)                            // если темпер < 22 включаем ОТОПЛЕНИЕ
    {
        switches_state |= HEATERS;
    }
    if (temperature_inside > 25 )
    {
        switches_state &= ~HEATERS;              // если темпер  > 25 отключаем ОТОПЛЕНИЕ
    }
    if (temperature_inside > 30)
    {
        switches_state |= CONDITIONER;           // если темпер >  30 включаем кондер
    }
    if (temperature_inside < 26)                 // если темпер < 25 и ниже  отключаем кондер
    {
        switches_state &= ~CONDITIONER;
    }
    return switches_state;
}
int garden_lighting(int i,bool movement,int switches_state)
{
    if (i < 5 && movement || i > 16 && i < 29 && movement || i > 40 && i < 48 && movement)   // если вечером есть движение - включаем свет
    {
        switches_state |= LIGHTS_OUTSIDE;
    }
    if (i < 5 && !movement || i > 16 && i < 29 && !movement || i > 40 && i < 48 && !movement)   // если вечером нет движения - ВЫключаем свет
    {
        switches_state &= ~LIGHTS_OUTSIDE;
    }
    if (i > 4 && i < 17 || i > 28 && i < 41)                                                   // в дневное время отключаем свет в саду
    {
        switches_state &= ~LIGHTS_OUTSIDE;
    }
    return switches_state;
}
void light_in_the_house(int i, bool lights, int switches_state)                               // НУЖНО ДОПИСАТЬ СВЕТ В ДОМЕ
{
    if (lights)
    {

    }
}


bool zero_bit(int switches_state, int index)            // проверка включен ли бит
{
    return (switches_state & (1 << index)) != 0;
}

int main()
{
    
    int switches_state = 0;                            // переменная, хранящая информацию о работающих датчиках
   // switches_state |= HEATERS;                       // чтобы включить обогреватель
    // switches_state &= ~HEATERS;                     // чтобы выключить обогреватель
    int temperature_inside = 0;
    int temperature_outside = 0;
    bool movement = "yes";
    bool lights = "on";
    std::string movement_word = "yes";
    std::string lights_word = "on";

    for (int i = 0; i < 48; i++)                       // создаем цикл-время навное 48ч ( двое суток)
    {
        std::cout << "Temperature inside, temperature outside, movement, lights: ";
        std::string teams;                              // переменная для комманд 
        std::getline(std::cin, teams);
        std::stringstream temp_stream(teams);           // создаем строковый поток
        temp_stream >> temperature_inside >> temperature_outside >> movement_word >> lights_word;

        
        movement = (movement_word == "yes") ? true : false;     // переводим в булевское значение строку да(1) или нет(0)
        lights = (lights_word == "on") ? true : false;          // переводим в булевское значение строку да(1) или нет(0)

        switches_state = water_pipe(temperature_outside, switches_state);
        switches_state = weather_in_the_house(temperature_inside, switches_state);
        switches_state = garden_lighting(i, movement, switches_state);

        (zero_bit(switches_state, HEATERS)) ? std::cout << "Heaters ON!\n" : std::cout << "Heaters OFF!\n";

        (zero_bit(switches_state, CONDITIONER)) ? std::cout << "Conditioner ON!\n" : std::cout << "Conditioner OFF!\n";

        (zero_bit(switches_state, LIGHTS_OUTSIDE)) ? std::cout << "Lights ON!\n" : std::cout << "Lights OFF!\n";
        
        (zero_bit(switches_state, WATER_PIPE_HEATING)) ? std::cout << "heating water supply ON!\n" : std::cout << "heating water supply OFF!\n";



        //std::cout << temperature_inside;
       // std::cout << temperature_outside;
        //std::cout << movement;
        //std::cout << lights;
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
