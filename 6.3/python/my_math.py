#
#   Application.cpp
#
#   Date: January 31st 2022
#   Author: Paul Mauviel
#

def MultiplicationTable(num: int) -> None:
    """ Displays a num by 10 multiplication table """
    for i in range(1, 10):
        print(num, 'X', i, '=', num * i)

def DoubleValue (num: int) -> int:
    """ Doubles a value and returns it """
    return num * 2
