#pragma once
#include <iostream>

class Command
{
public:
	Command();
	virtual ~Command() = default;
	Command(const Command& other) = delete;
	Command(Command&& other) = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) = delete;
	
	virtual void Execute() = 0;
};

class FireCommand final : public Command
{
public:
	FireCommand() {};
	void Execute() override { std::cout << "Fire...\n"; };
};

class JumpCommand final : public Command
{
public:
	JumpCommand() {};
	void Execute() override { std::cout << "Jump...\n"; };
};

class DriveCommand final : public Command
{
public:
	DriveCommand() {};
	void Execute() override { std::cout << "Drive...\n"; };
};

class BananaCommand final : public Command
{
public:
	BananaCommand() {};
	void Execute() override { std::cout << "Banana...\n"; };
};

class QuitCommand final : public Command
{
public:
	QuitCommand(bool* quit) { m_ShouldQuit = quit; };
	void Execute() override { *m_ShouldQuit = !(*m_ShouldQuit); };
private:
	bool* m_ShouldQuit;
};