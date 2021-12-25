#ifndef BUTTON_CHKH
#define BUTTON_CHKH
#include "common.h"

/* マクロ定義 */
#define SW_OFF 0 // Button OFF状態
#define SW_ON  1 // Button ON状態
#define SW_UNKNOWN 2 // Button状態不明

class Button{
    UCHR status;
    public:
    char buttonCheck(void);
};

#endif /* BUTTON_CHKH */