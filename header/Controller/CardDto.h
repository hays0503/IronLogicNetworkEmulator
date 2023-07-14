#ifndef CARDDTO_H
#define CARDDTO_H

#include "header/IronLogicDependency/ZGuard.h"
#include "qlist.h"
#include "qtypes.h"

struct CardDtoAndIndex
{
    qint32 indexInController;
    _ZG_CTR_KEY KeyInfo;
};

struct CartDto
{
    QHash<QString,CardDtoAndIndex>* KeyInController;
    QList<int>* EmptyKeyIndexInController;
};

#endif // CARDDTO_H
