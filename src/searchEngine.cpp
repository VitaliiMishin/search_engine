#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "converterJson.h"
#include "invertedIndex.h"
#include "searchServer.h"
#include "customExeptions.h"

int main()
{

    time_t startTime = time(nullptr);

    std::string  pathToJson = "json/";
    std::vector<std::string> queriesInput;
    int responsesLimit;
    ConverterJson converterJson(pathToJson);
    InvertedIndex invertedIndex;
    try
    {
        converterJson.GetConfig();
        invertedIndex.docs = converterJson.GetTextDocuments();
        queriesInput = converterJson.GetRequests();
        responsesLimit = converterJson.GetResponsesLimit();
        invertedIndex.UpdateDocumentBase(invertedIndex.docs);
    }
    catch (const std::exception &exception)
    {
        std::cerr << exception.what() << std::endl;
        return 0;
    }
    SearchServer searchServer(std::move(invertedIndex));
    std::vector<std::vector<RelativeIndex>> answers = searchServer.search(queriesInput, responsesLimit);
    try
    {
        converterJson.putAnswers(answers);
    }
    catch (const AnswersFileNotOpen &exception)
    {
        std::cerr << exception.what() << std::endl;
        return 0;
    }

    time_t finishTime = time(nullptr);
    std::cout << "Search completed after " << std::difftime(finishTime,startTime) << " seconds." << std::endl;

    return 0;
}