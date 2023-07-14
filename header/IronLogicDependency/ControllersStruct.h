#ifndef CONTROLLERSSTRUCT_H
#define CONTROLLERSSTRUCT_H

#include <Windows.h>



LPCTSTR EvTypeStrs[] = {
    TEXT(""),
    TEXT("Open button"),				// Открыто кнопкой изнутри
    TEXT("Key not found"),				// Ключ не найден в банке ключей
    TEXT("Open key"),					// Ключ найден, дверь открыта
    TEXT("Key unscheduled"),			// Ключ найден, доступ не разрешен
    TEXT("Open RS485"),					// Открыто оператором по сети
    TEXT("Door is blocked (key)"),		// Ключ найден, дверь заблокирована
    TEXT("Door is blocked (button)"),	// Попытка открыть заблокированную дверь кнопкой
    TEXT("Door is broken"),				// Дверь взломана
    TEXT("Door is left open"),			// Дверь оставлена открытой (timeout)
    TEXT("Passage"),					// Проход состоялся
    TEXT("Sensor 1"),					// Сработал датчик 1
    TEXT("Sensor 2"),					// Сработал датчик 2
    TEXT("Controller is rebooted"),		// Перезагрузка контроллера
    TEXT("Button is disabled"),			// Заблокирована кнопка открывания
    TEXT("Double pass"),				// Попытка двойного прохода
    TEXT("Door opened"),				// Дверь открыта штатно
    TEXT("Door closed"),				// Дверь закрыта
    TEXT("Power off"),					// Пропало питание
    TEXT("Power is on (ElectroControl)"),	// Включение электропитания
    TEXT("Power is off (ElectroControl)"),	// Включение электропитания
    TEXT("Enable the lock (trigger)"),		// Включение замка (триггер)
    TEXT("Disable the lock (trigger)"),	// Отключение замка (триггер)
    TEXT("Changed state Mode"),			// Изменение состояния Режим
    TEXT("Changed state Fire"),			// Изменение состояния Пожара
    TEXT("Changed state Security"),		// Изменение состояния Охраны
    TEXT("Unknown key"),				// Неизвестный ключ
    TEXT("Passage in the gateway"),		// Совершен вход в шлюз
    TEXT("Blocked the entrance to the gateway (busy)"),		// Заблокирован вход в шлюз (занят)
    TEXT("Allowed to enter the gateway"),	// Разрешен вход в шлюз
    TEXT("AntiPassBack"),				// Заблокирован проход (Антипассбек)
    TEXT("Hotel40"),
    TEXT("Hotel41")
};

LPCTSTR DirectStrs[] = {
    TEXT(""),
    TEXT("IN"),   // Вход
    TEXT("OUT")   // Выход
};

LPCTSTR EcSubEvStrs[] = {
    TEXT(""),
    TEXT("CARD_DELAY"),			// Поднесена валидная карта с другой стороны (для входа) запущена задержка
    TEXT("RESERVED1"),			// (зарезервировано)
    TEXT("ON_NET"),				// Включено командой по сети
    TEXT("OFF_NET"),			// Выключено командой по сети
    TEXT("ON_SCHED"),			// Включено по временной зоне
    TEXT("OFF_SHED"),			// Выключено по временной зоне
    TEXT("CARD"),				// Поднесена валидная карта к контрольному устройству
    TEXT("RESERVED2"),			// (зарезервировано)
    TEXT("OFF_TIMEOUT"),		// Выключено после отработки таймаута
    TEXT("OFF_EXIT")			// Выключено по срабатыванию датчика выхода
};

LPCTSTR FireSubEvStrs[] = {
    TEXT(""),
    TEXT("OFF_NET"),			// Выключено по сети
    TEXT("ON_NET"),				// Включено по сети
    TEXT("OFF_INPUT_F"),		// Выключено по входу FIRE
    TEXT("ON_INPUT_F"),			// Включено по входу FIRE
    TEXT("OFF_TEMP"),			// Выключено по датчику температуры
    TEXT("ON_TEMP")				// Включено по датчику температуры
};

LPCTSTR SecurSubEvStrs[] = {
    TEXT(""),
    TEXT("OFF_NET"),			// Выключено по сети
    TEXT("ON_NET"),				// Включено по сети
    TEXT("OFF_INPUT_A"),		// Выключено по входу ALARM
    TEXT("ON_INPUT_A"),			// Включено по входу ALARM
    TEXT("OFF_TAMPERE"),		// Выключено по тамперу
    TEXT("ON_TAMPERE"),			// Включено по тамперу
    TEXT("OFF_DOOR"),			// Выключено по датчику двери
    TEXT("ON_DOOR")				// Включено по датчику двери
};

LPCTSTR ModeSubEvStrs[] = {
    TEXT(""),
    TEXT("RS485 allow"),		// Установка командой по сети
    TEXT("RS485 denied"),		// Отказано оператору по сети
    TEXT("Timezone start"),			// Началась временная зона
    TEXT("Timezone finish"),			// Окончилась временная зона
    TEXT("Card allow"),			// Установка картой
    TEXT("Card denied")			// Отказано изменению картой
};

LPCTSTR ModeStrs[] = {
    TEXT(""),
    TEXT("Norm"),				// Норма
    TEXT("Block"),				// Блокировка
    TEXT("Free"),				// Свободный
    TEXT("Wait")				// Ожидание
};

LPCTSTR HModeStrs[] = {
    TEXT(""),
    TEXT("Norm"),				// Норма
    TEXT("Block"),				// Блокировка
    TEXT("Free"),				// Свободный
    TEXT("???")					// Зарезервировано
};

LPCTSTR HotelSubEvStrs[] = {
    TEXT(""),
    TEXT("FreeCard"),			// Карта открытия
    TEXT("BlockCard"),			// Карта блокирующая
    TEXT("DopFunc"),			// Дополнительная функция
    TEXT("NewRCard"),			// создана резервная карта
    TEXT("Network"),
    TEXT("Timezone"),
    TEXT("Counter"),			// обновлен счетчик
    TEXT("CryptoKey"),			// обновлен криптоключ
    TEXT("Pulse Z"),			// измененение защелки в течении 2х секунд
    TEXT("State Change")		// состояние защелки -если нажали ручку и отпустили более чем через 2 секунды
};





#endif // CONTROLLERSSTRUCT_H
