#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Forward declaration
class WeatherData;

// Abstract base class for observers
class WeatherObserver
{
public:
    virtual void update(const WeatherData &data) = 0;
    virtual ~WeatherObserver() {}
};

// Concrete observer: DisplayObserver
class DisplayObserver : public WeatherObserver
{
public:
    void update(const WeatherData &data) override;
};

// Concrete observer: MobileAlertObserver
class MobileAlertObserver : public WeatherObserver
{
private:
    float temperatureThreshold;

public:
    MobileAlertObserver(float threshold) : temperatureThreshold(threshold) {}
    void update(const WeatherData &data) override;
};

// Concrete observer: StatisticsObserver
class StatisticsObserver : public WeatherObserver
{
private:
    std::vector<float> temperatureHistory;

public:
    void update(const WeatherData &data) override;
    void showStatistics() const;
};

// Subject: WeatherData
class WeatherData
{
private:
    std::vector<WeatherObserver *> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    void addObserver(WeatherObserver *observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(WeatherObserver *observer)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setMeasurements(float temp, float hum, float pres)
    {
        temperature = temp;
        humidity = hum;
        pressure = pres;
        notifyObservers();
    }

    void notifyObservers() const
    {
        for (auto observer : observers)
        {
            observer->update(*this);
        }
    }

    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }
    float getPressure() const { return pressure; }
};

// Implementations of Concrete Observers

void DisplayObserver::update(const WeatherData &data)
{
    std::cout << "DisplayObserver: Temperature = " << data.getTemperature()
              << ", Humidity = " << data.getHumidity()
              << ", Pressure = " << data.getPressure() << std::endl;
}

void MobileAlertObserver::update(const WeatherData &data)
{
    if (data.getTemperature() > temperatureThreshold)
    {
        std::cout << "MobileAlertObserver: Alert! Temperature exceeded " << temperatureThreshold
                  << " degrees. Current temperature = " << data.getTemperature() << std::endl;
    }
}

void StatisticsObserver::update(const WeatherData &data)
{
    temperatureHistory.push_back(data.getTemperature());
    std::cout << "StatisticsObserver: Recorded temperature = " << data.getTemperature() << std::endl;
}

void StatisticsObserver::showStatistics() const
{
    std::cout << "StatisticsObserver: Temperature History: ";
    for (float temp : temperatureHistory)
    {
        std::cout << temp << " ";
    }
    std::cout << std::endl;
}

// Client Code
int main()
{
    WeatherData weatherData;

    DisplayObserver displayObserver;
    MobileAlertObserver mobileAlertObserver(30.0); // Alert if temperature exceeds 30
    StatisticsObserver statisticsObserver;

    // Register observers
    weatherData.addObserver(&displayObserver);
    weatherData.addObserver(&mobileAlertObserver);
    weatherData.addObserver(&statisticsObserver);

    // Simulate weather data updates
    std::cout << "Updating weather data...\n";
    weatherData.setMeasurements(28.5, 65.0, 1013.0);

    std::cout << "\nUpdating weather data...\n";
    weatherData.setMeasurements(32.0, 70.0, 1012.0);

    // Deregister MobileAlertObserver
    std::cout << "\nDeregistering MobileAlertObserver...\n";
    weatherData.removeObserver(&mobileAlertObserver);

    std::cout << "\nUpdating weather data...\n";
    weatherData.setMeasurements(25.0, 60.0, 1011.0);

    // Display statistics
    statisticsObserver.showStatistics();

    return 0;
}
