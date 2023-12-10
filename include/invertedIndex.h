#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <thread>
#include <mutex>
#include "customExeptions.h"

struct Entry {
    size_t docId, count;
    // Данный оператор необходим для проведения тестовых сценариев
    bool operator == (const Entry& other) const {
        return (docId == other.docId && count == other.count);
    }
};
class InvertedIndex {

public:
    InvertedIndex() = default;
    InvertedIndex(const InvertedIndex && moved)  noexcept {freqDictionary = moved.freqDictionary; docs = moved.docs; defaultThreads = moved.defaultThreads;};
    /**
    * Обновить или заполнить базу документов, по которой будем совершать поиск*
    @param inputDocs содержимое документов
    */
    void UpdateDocumentBase(const std::vector<std::string> inputDocs);
    /**
    * Метод определяет количество вхождений слова word в загруженной базе документов
    * @param word слово, частоту вхождений которого необходимо определить
    * @return возвращает подготовленный список с частотой слов
    */
    std::vector<Entry> GetWordCount(const std::string& word);

    int defaultThreads = 4;
    std::map<std::string, std::vector<Entry>> freqDictionary; // частотный словарь
    std::vector<std::string> docs; // список содержимого документов
private:
    void StartThread(const std::vector<std::string> &inputDocs, size_t &docId, size_t maxDocId);
    std::mutex dictionaryAccess;
    std::mutex docsAccess;
};
