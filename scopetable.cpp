
using namespace std;

class separate_chaining
{
private:
    linked_list *array_of_linked_list;
    int size;
    unsigned int (*hash)(string);
    int collision = 0;
    int probe = 0;
    int duplicate = 0;

public:
    separate_chaining(int s, unsigned int (*h)(string)) : size(s), hash(h)
    {
        array_of_linked_list = new linked_list[s];
    }
    ~separate_chaining();

    int getCollision() { return collision; }
    int getDuplicate() { return duplicate; }
    int getProbe() { return probe; }

    bool insert(string key, int value)
    {
        auto x = this->search(key, true);
        if (x.second == nullptr)
        {
            // not found, now insert
            this->array_of_linked_list[x.first].insert(key, value);
            return true;
        }
        return false;
    }

    pair<int, node *> search(string key, bool inserting = false, bool probe_finding = false)
    {
        unsigned int idx = this->hash(key) % size;
        auto x = this->array_of_linked_list[idx].getHead();
        if (inserting && x != nullptr)
        {
            this->collision++;
        }
        while (x != nullptr)
        {
            if (x->getKey() == key)
            {
                if (inserting)
                    this->duplicate++;
                return make_pair(idx, x);
            }
            if (probe_finding)
            {
                this->probe++;
            }
            x = x->nextNode();
        }
        return {idx, nullptr};
    }

    bool dlt(string key)
    {
        auto x = search(key);
        if (x.second == nullptr)
        {
            return false;
        }
        this->array_of_linked_list[x.first].dlt(key);
        return true;
    }
};

separate_chaining::~separate_chaining()
{
}
