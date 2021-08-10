#include <iostream>
#include <string>
#include <set>
#include <map>
#include <climits>
#include <iterator>
#include <fstream>
#include <chrono>
#include <list>
#include <algorithm>
#include <vector>
#define ALPHA_SIZE 26
using namespace std;

//HASHMAP
struct LLNode
{
    string key;
    LLNode *next;
    LLNode(string key) : key(key), next(nullptr){};
};
class LL
{
private:
public:
    LLNode *head = nullptr;
    LL(string key) { push(key); };

    void push(string key)
    {
        LLNode *newone = new LLNode(key);
        if (head == nullptr)
        {
            head = newone;
        }
        else
        {
            LLNode *crawler = head;
            while (crawler->next != nullptr)
            {
                crawler = crawler->next;
            }
            crawler->next = newone;
        }
    }
    bool search(string key)
    {
        LLNode *crawler = head;
        while (crawler != nullptr)
        {
            if (crawler->key == key)
            {
                return true;
            }
            crawler = crawler->next;
        }
        return false;
    }
};
int hasher(string key)
{
    unsigned int result = 0, temp = 1, keysize = key.size();

    for (int i = keysize - 1; i >= 0; i--)
    {
        result += temp * (key[i] - 'a');
        temp *= ALPHA_SIZE;
        result %= 2147483647;
    }
    return result;
}
class HashMap
{
private:
    int size = 0;
    map<int, LL> mymap;

public:
    //insertion
    void insert(string key)
    {
        int hash_val = hasher(key);
        map<int, LL>::iterator iter = mymap.find(hash_val);
        if (iter == mymap.end())
        {
            LL newone(key);
            mymap.insert(pair<int, LL>(hash_val, newone));
        }
        else
        {
            iter->second.push(key);
        }
        size++;
    }
    //search
    bool search(string key)
    {
        int hash_val = hasher(key);
        map<int, LL>::iterator iter = mymap.find(hash_val);
        if (iter == mymap.end())
        {
            return false;
        }
        else
        {
            return iter->second.search(key);
        }
    }
};
//TRIES
// trie node
struct TNode
{
    struct TNode *children[ALPHA_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};
struct TNode *createNode(void)
{
    struct TNode *pNode = new TNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHA_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}
// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TNode *root, string key)
{
    struct TNode *crawler = root;
    unsigned str_size = key.size();
    for (int i = 0; i < str_size; i++)
    {
        int index = key[i] - 'a';
        if (!crawler->children[index])
            crawler->children[index] = createNode();

        crawler = crawler->children[index];
    }

    // mark last node as leaf
    crawler->isEndOfWord = true;
}
// Returns true if key presents in trie, else
// false
bool search(struct TNode *root, string key)
{
    struct TNode *crawler = root;
    unsigned str_size = key.size();
    for (int i = 0; i < str_size; i++)
    {
        int index = key[i] - 'a';
        if (!crawler->children[index])
            return false;

        crawler = crawler->children[index];
    }

    return (crawler->isEndOfWord);
}

int main()
{
    //initializing the variables we need
    std::chrono::nanoseconds current(0);
    std::chrono::nanoseconds total(0);
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    ifstream input_data;
    fstream word_list;
    ofstream benches;
    vector<string> words;
    // getting the files we need loaded
    word_list.open("C:\\new_words.txt");
    input_data.open("C:\\new_text.txt");
    benches.open("C:\\benches.txt");
    std::string Text_input((std::istreambuf_iterator<char>(input_data)),
                           (std::istreambuf_iterator<char>()));

    //LINEAR SEARCH
    end = std::chrono::steady_clock::now();
    list<string> *mylist = new list<string>;
    string temp;
    std::cout << "list,";
    start = std::chrono::steady_clock::now();
    for (int i = 0; i < 69903; i++)
    {
        std::getline(word_list, temp);
        mylist->push_back(temp);
    }
    end = std::chrono::steady_clock::now();
    current = end - start;
    std::cout << current.count() << ",";
    //   << mylist->size() << "\nSearch time:";
    total = std::chrono::nanoseconds::zero();
    //iterate mylist
    // for (list<string>::iterator i = mylist->begin(); i != mylist->end();i++){
    //     std::cout << *i << "\n";
    // }
    //initializing the variables we need
    // i - iterator for the input text
    // j - start index of a word

    unsigned int i = 0, j = 0, success = 0, fail = 0, tsize = Text_input.size();
    bool first_letter = 1;
    list<string>::iterator it;
    //initializing time measurement
    //text transformation into spaces and lowercase letters
    //unless the text is not ended, do
    while (Text_input[i] != '\0' && i < tsize)
    {
        first_letter = 1;
        //find a word cycle
        // until the char from text is not space, do
        while (Text_input[i] == ' ' || Text_input[i] == '\n')
        {
            i++;
        }
        while (Text_input[i] != ' ')
        {
            //if the character is a capital letter, make it lower
            if ((int)Text_input[i] > 64 && (int)Text_input[i] < 91)
            {
                Text_input[i] += 32;
                if (first_letter)
                {
                    j = i;
                    first_letter = 0;
                }
            }
            else if ((int)Text_input[i] > 96 && (int)Text_input[i] < 123)
            {
                if (first_letter)
                {
                    j = i;
                    first_letter = 0;
                }
            }
            // and any other character turn into space
            else
            {
                Text_input[i] = ' ';
                continue;
            }
            i++;
            // std::cout << i << "," << tsize << "\n";
        }

        //search part
        //after the word is found
        //search  for it in the list
        if (!first_letter)
        {
            temp = Text_input.substr(j, i - j);
            words.push_back(temp);
            // std::cout << i - j << "," << temp.size() << "," << temp << "\n";
            start = std::chrono::steady_clock::now();
            it = std::find(mylist->begin(), mylist->end(), temp);
            end = std::chrono::steady_clock::now();
            current = end - start;
            total += current;
            if (it == mylist->end())
                fail++;
            else
                success++;
        }
        if (i > tsize)
        {
            i = tsize;
        }
    }
    mylist->clear();
    delete mylist;
    std::cout << total.count() << ",";
    std::cout << success << "," << fail << "\n";

    // input_data << Text_input;
    total = std::chrono::nanoseconds::zero();
    word_list.clear();
    word_list.seekg(0);
    unsigned int word_vec_size = words.size();

    //BBST
    set<string, greater<string>> *myset = new set<string, greater<string>>;
    set<string, greater<string>>::iterator itr;
    //dictionary creation
    std::cout << "SET,";
    for (i = 0; i < 69903; i++)
    {
        std::getline(word_list, temp);
        start = std::chrono::steady_clock::now();
        myset->insert(temp);
        end = std::chrono::steady_clock::now();
        current = end - start;
        total += current;
    }
    std::cout << total.count() << ",";
    total = std::chrono::nanoseconds::zero();
    //END

    //search part

    i = j = success = fail = 0;
    for (; i < word_vec_size; i++)
    {
        temp = words[i];
        start = std::chrono::steady_clock::now();
        itr = myset->find(temp);
        end = std::chrono::steady_clock::now();
        current = end - start;
        total += current;
        if (itr == myset->end())
            fail++;
        else
            success++;
    }
    std::cout << total.count() << ",";
    std::cout << success << "," << fail << "\n";
    delete myset;
    total = chrono::nanoseconds::zero();
    word_list.clear();
    word_list.seekg(0);
    success = fail = 0;
    //TRIES
    struct TNode *root_er = createNode();
    start = std::chrono::steady_clock::now();
    for (i = 0; i < 69903; i++)
    {
        std::getline(word_list, temp);
        insert(root_er, temp);
    }
    end = std::chrono::steady_clock::now();
    current = end - start;
    std::cout << "Tries," << current.count() << ",";
    total = chrono::nanoseconds::zero();
    bool booler;
    //search part
    for (i = 0; i < word_vec_size; i++)
    {
        temp = words[i];
        start = std::chrono::steady_clock::now();
        booler = search(root_er, temp);
        end = std::chrono::steady_clock::now();
        current = end - start;
        total += current;
        if (booler)
        {
            success++;
        }
        else
            fail++;
    }
    std::cout << total.count() << ",";
    std::cout << success << "," << fail << "\n";
    delete root_er;
    total = chrono::nanoseconds::zero();
    word_list.clear();
    word_list.seekg(0);

    //HASHMAP
    HashMap HnM;
    //dictionary creation
    std::cout << "HashMap,";
    start = std::chrono::steady_clock::now();
    for (i = 0; i < 69903; i++)
    {
        getline(word_list, temp);
        HnM.insert(temp);
    }
    end = std::chrono::steady_clock::now();
    current = end - start;
    std::cout << current.count() << ",";
    success = fail = 0;
    total = std::chrono::nanoseconds::zero();
    for (i = 0; i < word_vec_size; i++)
    {
        temp = words[i];
        start = std::chrono::steady_clock::now();
        booler = HnM.search(temp);
        end = std::chrono::steady_clock::now();
        current = end - start;
        total += current;
        if (booler)
            success++;
        else
            fail++;
    }
    std::cout << total.count() << ",";
    std::cout << success << "," << fail;
    word_list.close();
    // cin >> temp;
}