#include "invertedIndex.h"

void InvertedIndex::StartThread(const std::vector<std::string> &inputDocs, size_t &docId, size_t maxDocId) {
    std::string doc;
    size_t docIndex;
    do {
        docsAccess.lock();
        docIndex = docId;
        ++docId;
        docsAccess.unlock();

        if (docIndex < maxDocId) {
            doc = inputDocs[docIndex];
            if(doc.empty()) {
                continue;
            }

            std::map<std::string, size_t> tempFreqDictionary;
            std::transform(doc.begin(), doc.end(), doc.begin(), [](char symbol) {
                symbol = std::tolower(symbol);
                if (symbol < 'a' || symbol > 'z') {
                    return ' ';
                } else {
                    return symbol;
                }
            });
            std::stringstream ssDoc{doc};
            std::string word;
            while (ssDoc >> word) {
                if (tempFreqDictionary.find(word) != tempFreqDictionary.end()) {
                    ++tempFreqDictionary[word];
                } else {
                    tempFreqDictionary[word] = 1;
                }
            }

            dictionaryAccess.lock();
            for (const auto &[word, count]: tempFreqDictionary) {
                freqDictionary[word].push_back({docIndex, count});
            }
            dictionaryAccess.unlock();
        }
    } while(docIndex < maxDocId);
}

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string> inputDocs) {

    if(inputDocs.empty()) {
        throw NoDocumentsToIndex();
    }

    int numberThreads = defaultThreads;
    if(defaultThreads > 1) {
        numberThreads = std::thread::hardware_concurrency();
        if(!numberThreads) {
            numberThreads = defaultThreads;
        }
    }

    size_t docId = 0;
    size_t maxDocId = inputDocs.size();
    if(maxDocId < numberThreads) {
        numberThreads = maxDocId;
    }

    std::vector<std::thread> threads;

    for (int i = 0; i < numberThreads; ++i) {
        threads.push_back(std::thread(&InvertedIndex:: StartThread, this, std::ref(inputDocs), std::ref(docId), maxDocId));
    }
    for (int i = 0; i < numberThreads; ++i) {
        threads[i].join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    std::string modifiedWord(word.length(), ' ');
    std::transform(word.begin(), word.end(), modifiedWord.begin(), ::tolower);
    if(freqDictionary.find(modifiedWord) != freqDictionary.end()) {
        return freqDictionary[modifiedWord];
    } else {
        std::vector<Entry> result;
        return result;
    }
}
