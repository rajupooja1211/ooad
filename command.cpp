#include <iostream>
#include <stack>
#include <memory>

// Command Interface
class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// Receiver Classes
class Light
{
public:
    void turnOn()
    {
        std::cout << "Light is ON" << std::endl;
    }
    void turnOff()
    {
        std::cout << "Light is OFF" << std::endl;
    }
};

class Fan
{
public:
    void turnOn()
    {
        std::cout << "Fan is ON" << std::endl;
    }
    void turnOff()
    {
        std::cout << "Fan is OFF" << std::endl;
    }
};

// Concrete Command Classes
class LightOnCommand : public Command
{
private:
    Light *light;

public:
    LightOnCommand(Light *l) : light(l) {}
    void execute() override
    {
        light->turnOn();
    }
    void undo() override
    {
        light->turnOff();
    }
};

class LightOffCommand : public Command
{
private:
    Light *light;

public:
    LightOffCommand(Light *l) : light(l) {}
    void execute() override
    {
        light->turnOff();
    }
    void undo() override
    {
        light->turnOn();
    }
};

class FanOnCommand : public Command
{
private:
    Fan *fan;

public:
    FanOnCommand(Fan *f) : fan(f) {}
    void execute() override
    {
        fan->turnOn();
    }
    void undo() override
    {
        fan->turnOff();
    }
};

class FanOffCommand : public Command
{
private:
    Fan *fan;

public:
    FanOffCommand(Fan *f) : fan(f) {}
    void execute() override
    {
        fan->turnOff();
    }
    void undo() override
    {
        fan->turnOn();
    }
};

// SmartHomeController Class
class SmartHomeController
{
private:
    std::stack<std::shared_ptr<Command>> commandHistory;

public:
    void executeCommand(std::shared_ptr<Command> command)
    {
        command->execute();
        commandHistory.push(command);
    }

    void undoLastCommand()
    {
        if (!commandHistory.empty())
        {
            auto lastCommand = commandHistory.top();
            lastCommand->undo();
            commandHistory.pop();
        }
        else
        {
            std::cout << "No commands to undo!" << std::endl;
        }
    }
};

// Client Code
int main()
{
    // Receivers
    Light light;
    Fan fan;

    // Commands
    auto lightOn = std::make_shared<LightOnCommand>(&light);
    auto lightOff = std::make_shared<LightOffCommand>(&light);
    auto fanOn = std::make_shared<FanOnCommand>(&fan);
    auto fanOff = std::make_shared<FanOffCommand>(&fan);

    // Controller
    SmartHomeController controller;

    // Execute commands
    std::cout << "Executing commands:" << std::endl;
    controller.executeCommand(lightOn);
    controller.executeCommand(fanOn);
    controller.executeCommand(lightOff);
    controller.executeCommand(fanOff);

    // Undo commands
    std::cout << "\nUndoing commands:" << std::endl;
    controller.undoLastCommand();
    controller.undoLastCommand();
    controller.undoLastCommand();
    controller.undoLastCommand();

    return 0;
}
