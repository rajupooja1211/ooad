#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Abstract Base Class
class Document
{
public:
    virtual void generate() const = 0;
    virtual void addWatermark(const std::string &text)
    {
        std::cout << "Adding watermark: " << text << std::endl;
    }
    virtual void addMetadata(const std::string &metadata)
    {
        std::cout << "Adding metadata: " << metadata << std::endl;
    }
    virtual void addTable(const std::vector<std::string> &tableData)
    {
        std::cout << "Adding table with data: ";
        for (const auto &data : tableData)
        {
            std::cout << data << " ";
        }
        std::cout << std::endl;
    }
    virtual ~Document() {}
};

// Concrete Class: PDFDocument
class PDFDocument : public Document
{
public:
    void generate() const override
    {
        std::cout << "Generating PDF Document..." << std::endl;
    }
};

// Concrete Class: WordDocument
class WordDocument : public Document
{
public:
    void generate() const override
    {
        std::cout << "Generating Word Document..." << std::endl;
    }
};

// Concrete Class: HTMLDocument
class HTMLDocument : public Document
{
public:
    void generate() const override
    {
        std::cout << "Generating HTML Document..." << std::endl;
    }
};

// Document Factory
class DocumentFactory
{
public:
    static std::unique_ptr<Document> createDocument(const std::string &type,
                                                    const std::vector<std::string> &features = {})
    {
        std::unique_ptr<Document> doc;
        if (type == "PDF")
        {
            doc = std::make_unique<PDFDocument>();
        }
        else if (type == "Word")
        {
            doc = std::make_unique<WordDocument>();
        }
        else if (type == "HTML")
        {
            doc = std::make_unique<HTMLDocument>();
        }
        else
        {
            throw std::invalid_argument("Unsupported document type");
        }

        // Add advanced features
        for (const auto &feature : features)
        {
            if (feature == "addWatermark")
            {
                doc->addWatermark("Confidential");
            }
            else if (feature == "addMetadata")
            {
                doc->addMetadata("Author: John Doe, Date: 2024-11-18");
            }
            else if (feature == "addTable")
            {
                doc->addTable({"Row1", "Row2", "Row3"});
            }
        }

        return doc;
    }
};

// Client Code
int main()
{
    try
    {
        std::string docType;
        std::cout << "Enter document type (PDF/Word/HTML): ";
        std::cin >> docType;

        std::vector<std::string> features;
        std::cout << "Add features? (e.g., addWatermark, addMetadata, addTable). Enter 'done' to finish:\n";
        std::string feature;
        while (true)
        {
            std::cin >> feature;
            if (feature == "done")
                break;
            features.push_back(feature);
        }

        auto document = DocumentFactory::createDocument(docType, features);
        document->generate();
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
