#include "gtest/gtest.h"
#include "converterJson.h"
#include "searchServer.h"
#include <nlohmann/json.hpp>

nlohmann::json configFile = {
        {"config", {
                {"name", "SkillboxSearchEngine"},
                {"version", "0.1"},
                {"max_responses", 5}}},
        {"files", {
                    "file001.txt",
                    "file002.txt",
                    "file003.txt",
                    "file004.txt",
                    "file005.txt",
                    "file006.txt",
                    "file007.txt",
                    "file008.txt",
                    "file009.txt",
                    "file010.txt",
                    "file011.txt",
                    "file012.txt",
                    "file013.txt",
                    "file014.txt",
                    "file015.txt"}}};

const std::vector<std::string> docs = {
        "london is the capital of great britain",
        "paris is the capital of france",
        "berlin is the capital of germany",
        "rome is the capital of italy",
        "madrid is the capital of spain",
        "lisbon is the capital of portugal",
        "bern is the capital of switzerland",
        "moscow is the capital of russia",
        "kiev is the capital of ukraine",
        "minsk is the capital of belarus",
        "astana is the capital of kazakhstan",
        "beijing is the capital of china",
        "tokyo is the capital of japan",
        "bangkok is the capital of thailand",
        "welcome to moscow the capital of russia the third rome"};

nlohmann::json requestsFile = {
        {"requests", {
                "london",
                "moscow is the capital of russia",
                "water milk"}}};

TEST(TestCaseConverterJson, GetConfig)
{
   nlohmann::json expected = R"({
       "config": {
           "max_responses": 5,
           "name": "SkillboxSearchEngine",
           "version": "0.1"
       },
       "files": [
            "file001.txt",
            "file002.txt",
            "file003.txt",
            "file004.txt",
            "file005.txt",
            "file006.txt",
            "file007.txt",
            "file008.txt",
            "file009.txt",
            "file010.txt",
            "file011.txt",
            "file012.txt",
            "file013.txt",
            "file014.txt",
            "file015.txt"
       ]
   })"_json;

    std::ofstream file("config.json");
    file << configFile.dump(4);
    file.close();

    ConverterJson converterJson("");
    converterJson.GetConfig();
    nlohmann::json config = converterJson.config;
    EXPECT_EQ(expected, config);
}

TEST(TestCaseConverterJson, GetTextDocuments)
{
    std::ofstream file("config.json");
    file << configFile.dump(4);
    file.close();

    for(int i = 0; i < docs.size(); ++i) {
        std::string text = "file" + std::to_string(i + 1001).erase(0, 1) + ".txt";
        std::ofstream textFile(text);
        textFile << docs[i];
        textFile.close();
    }

    ConverterJson converterJson("");
    converterJson.GetConfig();

    std::vector<std::string> texts = converterJson.GetTextDocuments();
    EXPECT_EQ(texts, docs);
}

TEST(TestCaseConverterJson, GetResponsesLimit)
{
    std::ofstream file("config.json");
    file << configFile.dump(4);
    file.close();

    ConverterJson converterJson("");
    converterJson.GetConfig();

    int responsesLimit = converterJson.GetResponsesLimit();
    EXPECT_EQ(responsesLimit, 5);
}

TEST(TestCaseConverterJson, GetRequests)
{
    std::ofstream file("config.json");
    file << configFile.dump(4);
    file.close();

    std::ofstream fileForRequests("requests.json");
    fileForRequests << requestsFile.dump(4);
    fileForRequests.close();

    ConverterJson converterJson("");
    converterJson.GetConfig();

    std::vector<std::string> requests = {
            "london",
            "moscow is the capital of russia",
            "water milk"};
    std::vector<std::string> queriesInput = converterJson.GetRequests();
    EXPECT_EQ(requests, queriesInput);
}

TEST(TestCaseConverterJson, PutAnswer)
{
    std::ofstream file("config.json");
    file << configFile.dump(4);
    file.close();

    ConverterJson converterJson("");
    converterJson.GetConfig();

    std::vector<std::vector<RelativeIndex>> answers = {
            {{0, 1.0f}},
            {{7, 1.0f}, {14, 1.0f}, {0, 0.6666666865348816f},
                        {1, 0.6666666865348816f}, {2, 0.6666666865348816f}},
            {}
    };

    nlohmann::json expected = R"({
    "answers": {
        "request001": {
            "docID": 0,
            "rank": 1.0,
            "result": "true"
        },
        "request002": {
            "relevance": [
                {
                    "docID": 7,
                    "rank": 1.0
                },
                {
                    "docID": 14,
                    "rank": 1.0
                },
                {
                    "docID": 0,
                    "rank": 0.6666666865348816
                },
                {
                    "docID": 1,
                    "rank": 0.6666666865348816
                },
                {
                    "docID": 2,
                    "rank": 0.6666666865348816
                }
            ],
            "result": "true"
        },
        "request003": {
            "result": "false"
        }
    }
})"_json;

    converterJson.putAnswers(answers);
    auto fileForAnswers = std::ifstream("answers.json");
    nlohmann::json answersFile = nlohmann::json::parse(fileForAnswers);
    fileForAnswers.close();
    EXPECT_EQ(expected, answersFile);
}