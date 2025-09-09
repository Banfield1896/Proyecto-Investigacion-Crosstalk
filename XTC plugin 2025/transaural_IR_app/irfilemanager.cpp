#include "irfilemanager.h"

#include <utility>

class IRFileManagerData : public QSharedData
{
public:
};

IRFileManager::IRFileManager()
    : data(new IRFileManagerData)
{}

IRFileManager::IRFileManager(const IRFileManager &rhs)
    : data{rhs.data}
{}

IRFileManager::IRFileManager(IRFileManager &&rhs)
    : data{std::move(rhs.data)}
{}

IRFileManager &IRFileManager::operator=(const IRFileManager &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

IRFileManager &IRFileManager::operator=(IRFileManager &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

IRFileManager::~IRFileManager() {}
