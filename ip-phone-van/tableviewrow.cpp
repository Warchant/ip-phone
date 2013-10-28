#include "tableviewrow.h"

tableViewRow::tableViewRow()
{

}

tableViewRow::~tableViewRow()
{
    delete this->values;
}

bool tableViewRow::getEditable() const
{
    return editable;
}

tableViewRow &tableViewRow::setEditable(bool value)
{
    editable = value;
    return this;
}




std::string *tableViewRow::getValues() const
{
    return values;
}

tableViewRow& tableViewRow::setValues(std::string *value)
{
    values = value;
    return this;
}




tableViewRow::getKey() const
{
    return key;
}

tableViewRow &tableViewRow::setKey(const std::string &value)
{
    key = value;
    return this;
}
