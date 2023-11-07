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


int main()
{
    
    int switches_state = 0;                            // переменная, хранящая информацию о работающих датчиках

    int color_temperature = 5000;
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

        if (temperature_outside < 0 && !(switches_state & WATER_PIPE_HEATING))     //  если темпер снаружи  < 0 и помпа выключена
        {
            switches_state |= WATER_PIPE_HEATING;                                  // включаем помпу
            std::cout << "Water pump heating ON!\n";
        }
        if (temperature_outside > 5 && (switches_state & WATER_PIPE_HEATING))      // если темпер  > 5  и помпа включена
        {
            switches_state &= ~WATER_PIPE_HEATING;                                 //  отключаем обогрев помпы
            std::cout << "Water pump heating OFF!\n";
        }

        if (temperature_inside < 22 && !(switches_state & HEATERS))                            // если темпер < 22 и отопление выключено
        {
            switches_state |= HEATERS;                                                        // включаем ОТОПЛЕНИЕ
            std::cout << "Heaters ON!\n";
        }
        if (temperature_inside > 25 && (switches_state & HEATERS))                            // если темпер  > 25 и отопление включено
        {
            switches_state &= ~HEATERS;                                                       //  отключаем ОТОПЛЕНИЕ
            std::cout << "Heaters OFF!\n";
        }

        if (temperature_inside > 29 && !(switches_state & CONDITIONER))                       // если темпер >  30 и кондиционер выключен
        {
            switches_state |= CONDITIONER;                                                    //   30 включаем кондер
            std::cout << "Conditioner ON!!\n";
        }
        if (temperature_inside < 25 && (switches_state & CONDITIONER))                 // если темпер < 25 и ниже и кондиционер включен отключаем кондер
        {
            switches_state &= ~CONDITIONER;                                            // отключаем кондер
            std::cout << "Conditioner OFF!!\n";
        }

        if (i < 5 && movement && !(switches_state & LIGHTS_OUTSIDE) || i > 16 && i < 29 && movement && !(switches_state & LIGHTS_OUTSIDE) || i > 40 && i < 48 && movement && !(switches_state & LIGHTS_OUTSIDE))   // если вечером есть движение и выключен свет 
        {
            switches_state |= LIGHTS_OUTSIDE;                                          // Включаем свет
            std::cout << "Lights ON!\n";
        }
        if (i < 5 && !movement && (switches_state & LIGHTS_OUTSIDE) || i > 16 && i < 29 && !movement && (switches_state & LIGHTS_OUTSIDE) || i > 40 && i < 48 && !movement && (switches_state & LIGHTS_OUTSIDE))   // если вечером нет движения и включен свет
        {
            switches_state &= ~LIGHTS_OUTSIDE;                                         // ВЫКЛЮЧАЕМ СВЕТ
            std::cout << "Lights OFF!\n";
        }
        if (i > 4 && i < 17 && (switches_state & LIGHTS_OUTSIDE) || i > 28 && i < 41 && (switches_state & LIGHTS_OUTSIDE))                                                   // в дневное время отключаем свет в саду,  если он был включен
        {
            switches_state &= ~LIGHTS_OUTSIDE;
            std::cout << "Lights OFF!\n";
        }
        // циклы для цветовой температуры внутри дома
       if (i >= 16 && i < 20)
        {
            color_temperature -= 575;
        }
        if (i == 24)
        {
            color_temperature = 5000;
        }
        if (i >= 40 && i < 44)
        {
            color_temperature -= 575;
        }
        if (lights)
        {
            std::cout << "Color temperature :" << color_temperature << "K\n";
        }

    }
       

        
    return 0;
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
