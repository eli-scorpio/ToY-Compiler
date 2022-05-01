
typedef struct HashNode
{
    char* key;
    char* value;
    struct HashNode* next;
}HashNode;

typedef struct
{
    int size;
    HashNode** hashArr;
}HashMap;


HashMap* CreateHashMap(int n);
int InsertHashMap(HashMap* hashMap, char* key, char* value);
char* GetHashMap(HashMap* hashMap, char* key);
void DeleteHashMap(HashMap* hashMap);
void PrintHashMap(HashMap* hashMap);
void hashMapTest(void);

