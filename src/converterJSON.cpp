#include "converterJSON.h"

void ConverterJSON::GetConfig() {
    std::ifstream configFile(path + "config.json");
    if (configFile.is_open()) {
        config = nlohmann::json::parse(configFile);
        configFile.close();
        if(!config.contains("config")) {
            throw ConfigFileIsEmpty();
        }
    } else {
        throw ConfigFileIsMissing();
    }
    if(config["config"]["name"] != name) {
        throw InvalidProgramName();
    }
    if(config["config"]["version"] != version) {
        throw IncorrectProgramVersion();
    }
    std::cout << config["config"]["name"].get<std::string>() << " version " << config["config"]["version"].get<std::string>() << std::endl;
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> docs;

    if (config.contains("files") && (!config["files"].is_null())) {
        for (int i = 0; i < config["files"].size(); ++i) {
            std::string pathToFile = config["files"][i];
            std::ifstream textFile(pathToFile);
            if (!textFile.is_open()) {
                std::cerr << "Text file missing: " << pathToFile << std::endl;
                docs.push_back("");
            } else {
                std::stringstream text;
                text << textFile.rdbuf();
                textFile.close();
                docs.push_back(text.str());
            }
        }
    } else {
        throw ConfigFileIsEmpty();
    }
    return docs;
}

int ConverterJSON::GetResponsesLimit() {
    if (config["config"].contains("max_responses")) {
        return config["config"]["max_responses"];
    } else {
        return defaultResponsesLimit;
    }
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream requestsFile(path + "requests.json");
    nlohmann::json requests;
    if (requestsFile.is_open()) {
        requests = nlohmann::json::parse(requestsFile);
        requestsFile.close();
    } else {
        throw RequestsFileIsMissing();
    }
    if(!requests.contains("requests") || (requests["requests"].is_null())) {
        throw RequestsFileIsEmpty();
    }
    std::vector<std::string> queries;
    for (int i = 0; i < requests["requests"].size(); ++i) {
        queries.push_back(requests["requests"][i]);
    }
    return queries;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers) {
    int maxResponses = ConverterJSON::GetResponsesLimit();
    nlohmann::json answersToFile;
    for(int i = 0; i < answers.size(); ++i) {
        int countResponses = maxResponses;
        std::string request = "request" + std::to_string(i + 1001).erase(0, 1);
        if (answers[i].empty())
            answersToFile["answers"][request]["result"] = "false";
        else {
            if(answers[i].size() < maxResponses) {
                countResponses = answers[i].size();
            }
            if(countResponses > 1) {
                for (int j = 0; j < countResponses; ++j) {
                    answersToFile["answers"][request]["relevance"].push_back({{"docID", answers[i][j].docId}, {"rank", answers[i][j].rank}});
                }
            } else {
                answersToFile["answers"][request] = {{"docID", answers[i][0].docId}, {"rank", answers[i][0].rank}};
            }
            answersToFile["answers"][request]["result"] = "true";
        }
    }
    std::ofstream answerFile(path + "answers.json");
    if (!answerFile.is_open()) {
        throw AnswersFileNotOpen();
    }
    answerFile << answersToFile.dump(4);
    answerFile.close();
}
