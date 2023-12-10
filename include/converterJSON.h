#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include "searchServer.h"
#include "customExeptions.h"

class ConverterJSON {
public:
    explicit ConverterJSON(std::string pathToJson) : path(std::move(pathToJson)) {};

    void GetConfig();
    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    std::vector<std::string> GetTextDocuments();
    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return
    */
    int GetResponsesLimit();
    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    std::vector<std::string> GetRequests();
    /**
    * Положить в файл answers.json результаты поисковых запросов
    */
    void putAnswers(std::vector<std::vector<RelativeIndex>> answers);

    nlohmann::json config;

private:

    std::string version = "0.1";
    std::string name = "SkillboxSearchEngine";
    std::string path;
    const int defaultResponsesLimit = 5;

};
