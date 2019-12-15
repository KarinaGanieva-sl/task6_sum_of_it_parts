#include <iostream>
using namespace std;
#include "parts.h"

NameContainer::~NameContainer() = default;
NameContainer partContainer;

void Part::describe(void)
{
    if(subparts.size() == 0)
    {
        cout<<"Part " << name << " doesn't have any subparts" << "\n";
        return;;
    }
    cout << "Part " << name << " subparts are:" << "\n";
    for (map<Part*,int>::iterator iter = subparts.begin(); iter != subparts.end(); iter++)
        cout << iter->second << " " << iter->first->name << '\n';
}

int Part::count_howmany(Part const *p) {
    return countRecursion(this, p);;
}

int Part::countRecursion(Part *now, Part const *p)
{
    int sum = 0;
    if(now == p)
        return 1;
    for (pair<Part*, int> subpart : now->subparts)
        sum += countRecursion(subpart.first, p) * subpart.second;
    return sum;
}

Part *NameContainer::lookup(string const &name)
{
    if(name_map.count(name) == 1)
        return name_map.at(name);
    Part* part = new Part(name);
    name_map.insert(pair<string,Part*>(name, part));
    return part;
}

void add_part(string const &x, int q, string const &y)
{
    partContainer.lookup(x)->subparts.insert(pair<Part*,int>(partContainer.lookup(y), q));
}
