/*
指针实现 G++申请内存会比正常的大一倍
核心思想：空间换时间
*/
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<algorithm>
using namespace std;

const int maxn = 26;

typedef struct TrieNode {
    int nCount;
    struct TrieNode *next[maxn];
}Trie;

Trie root;

void InitTrie() {
    for (int i = 0; i < maxn; i++)
        root.next[i] = NULL;
}

void CreateTrie(char *str) {
    int len = strlen(str);
    Trie *p = &root, *q;
    for (int i = 0; i < len; i++) {
        int k = str[i] - 'a';
        if (p->next[k] == NULL) {
            q = (Trie *)malloc(sizeof(root));
            q->nCount = 1;
            for (int j = 0; j < maxn; j++)
                q->next[j] = NULL;
            p->next[k] = q;
            p = p->next[k];
        }
        else {
            p->next[k]->nCount++;
            p = p->next[k];
        }
    }
}

int FindTrie(char *str) {
    int len = strlen(str);
    Trie *p = &root;
    for (int i = 0; i < len; i++) {
        int k = str[i] - 'a';
        if (p->next[k] == NULL) return 0;
        p = p->next[k];
    }
    return p->nCount;
}

int main() {
    char str[15];
    InitTrie();
    while (gets(str) && str[0]) CreateTrie(str);
    while (gets(str)) printf("%d\n", FindTrie(str));
    return 0;
}
/*
静态数组实现
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int trie[maxn][26] = {0}; // 存储下一个字符的位置
int num[maxn] = {0};
int pos = 1;

void InsertTrie(char word[]) {
    int c = 0;
    for (int i = 0; word[i]; i++) {
        int k = word[i] - 'a';
        if (trie[c][k] == 0) trie[c][k] = pos++;
        c = trie[c][k];
        num[c]++;
    }
}


int FindTrie(char word[]) {
    int c = 0;
    for (int i = 0; word[i]; i++) {
        int k = word[i] - 'a';
        if (trie[c][k] == 0) return 0;
        c = trie[c][k];
    }
    return num[c];
}

int main() {
    char str[15] = {0};
    while (gets(str) && str[0]) InsertTrie(str);
    while (gets(str)) printf("%d\n", FindTrie(str));
    return 0;
}
