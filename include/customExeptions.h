#pragma once

#include <exception>

class ConfigFileIsMissing : public std::exception {
public:
    const char* what() const noexcept override {
        return "Config file is missing";
    }
};

class ConfigFileIsEmpty : public std::exception {
public:
    const char* what() const noexcept override {
        return "Config file is empty!";
    }
};

class RequestsFileIsMissing : public std::exception {
public:
    const char* what() const noexcept override {
        return "Requests file is missing!";
    }
};

class RequestsFileIsEmpty : public std::exception {
public:
    const char* what() const noexcept override {
        return "Requests file is empty!";
    }
};

class NoDocumentsToIndex : public std::exception {
public:
    const char* what() const noexcept override {
        return "No documents to index!";
    }
};

class AnswersFileNotOpen : public std::exception {
public:
    const char* what() const noexcept override {
        return "Answers file not open!";
    }
};

class InvalidProgramName : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid program name!";
    }
};

class IncorrectProgramVersion : public std::exception {
public:
    const char* what() const noexcept override {
        return "Incorrect program version!";
    }
};