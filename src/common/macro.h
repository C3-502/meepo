//
// Created by lxy on 2018/2/27.
//

#ifndef MEEPO_MACRO_H
#define MEEPO_MACRO_H

#define BV(x) (1 << x)

#define DISABLE_COPY(cls) \
    public: \
        cls(const cls &) = delete; \
        cls &operator=(const cls &) = delete;

#endif //MEEPO_MACRO_H
