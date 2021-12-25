#ifndef NUMBER_H_
#define NUMBER_H_

class Number{
    char number;
    char maxNumber;
    char minNumber;
    public:
    Number(void);
    Number(char max, char min);
    char getNumber();
};

#endif /* NUMBER_H_ */