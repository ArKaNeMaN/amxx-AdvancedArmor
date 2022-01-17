#if defined _advanced_armor_included
    #endinput
#endif
#define _advanced_armor_included

/**
 * Установка значения брони игрока.
 *
 * @param UserId    Индекс игрока.
 * @param iAmount   Значение брони.
 *
 * @noreturn
 */
native AdvArmor_SetUserArmor(const UserId, const iAmount);

/**
 * Добавление/убавление значения брони игрока.
 *
 * @param UserId    Индекс игрока.
 * @param iAmount   Значение брони.
 *
 * @noreturn
 */
native AdvArmor_AddUserArmor(const UserId, const iAmount, const iMax = 100);

/**
 * Получение текущего значения брони игрока.
 *
 * @param UserId    Индекс игрока.
 *
 * @return  Текущее значение брони игрока.
 */
native AdvArmor_GetUserArmor(const UserId);
