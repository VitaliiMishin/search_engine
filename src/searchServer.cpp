#include "searchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queriesInput, int responsesLimit) {
    std::vector<std::vector<RelativeIndex>> result(queriesInput.size());
    int docsCount = _index.docs.size();

    std::string request;
    for(int i = 0; i < queriesInput.size(); ++i) {
        request = queriesInput[i];
        std::transform(request.begin(), request.end(), request.begin(), [](char symbol) {
            symbol = std::tolower(symbol);
            if(symbol < 'a' || symbol > 'z'){
                return ' ';
            } else {
                return symbol;
            }
        });

        std::stringstream ssDoc{request};
        std::string word;
        std::vector<size_t> countWords(docsCount, 0);
        size_t maxCount = 0;
        while (ssDoc >> word) {
            if(_index.freqDictionary.count(word) > 0) {
                for(int j = 0; j < docsCount; ++j) {
                    auto tempFreqDictionary = _index.freqDictionary[word];
                    auto it = std::find_if(tempFreqDictionary.begin(), tempFreqDictionary.end(), [&] (Entry a){return a.docId == j;});
                    if(it != tempFreqDictionary.end()) {
                        countWords[j] += it -> count;
                        if(countWords[j] > maxCount) {
                            maxCount = countWords[j];
                        }
                    }
                }
            }
        }
        float rank;
        for(size_t k = 0; k < docsCount; ++k) {
            if(countWords[k] != 0) {
                rank = (float) countWords[k] / maxCount;
                result[i].push_back({k, rank});
            }
        }
        if(!result[i].empty()) {
            std::sort(result[i].begin(), result[i].end(), [](const RelativeIndex &previous, const RelativeIndex &next) {
                if (previous.rank == next.rank) {
                    return previous.docId < next.docId;
                } else {
                    return previous.rank > next.rank;
                }
            });
            if(result[i].size() > responsesLimit){
                result[i].resize(responsesLimit);
            }
        }
    }
    return result;
}