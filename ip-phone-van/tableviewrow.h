#ifndef TABLEVIEWROW_H
#define TABLEVIEWROW_H

#include <string>

class tableViewRow
{
public:
    tableViewRow();
    ~tableViewRow();

    bool getEditable() const;
    tableViewRow& setEditable(bool value);

    std::string getKey() const;
    tableViewRow& setKey(const std::string &value);

    std::string *getValues() const;
    tableViewRow& setValues(std::string *value);



private:
    std::string key;
    std::string *values;
    bool editable;
};

#endif // TABLEVIEWROW_H
