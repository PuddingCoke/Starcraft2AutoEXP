#pragma once

#include"Color.h"

//测试分辨率 2560 1440

//以下信息用来判断游戏状态 主界面 战斗 结算界面等等
//主菜单界面 469 1091 254 254 254
//战斗界面 1231 81 68 156 100
//任务成功 1472 888 0 254 136

//准备游戏按钮位置 267 1268
//结算按钮位置 308 1132


//五个虚空碎片位置
//307 1289
//229 1182
//94 1176
//94 1296
//205 1335

//极性因子 188 62 70
//0 2515 535
//1 2515 625
//2 2515 715
//3 2515 805

class Script
{
public:

	//脚本自动化一局
	void start()
	{
		//开始界面
		waitForColor(469, 1091, Color(254, 254, 254));
		setCursor(267, 1268);
		sendClick();

		//等待战斗
		waitForColor(1231, 81, Color(68, 156, 100));
		//突变因子有可能会晚点出来所以得等一下
		Sleep(500);

		bool hasFactor = checkFactors();

		//分别处理一下是否有极性因子
		if (hasFactor)
		{
			sendKey(VK_F10);
			sendKey('Q');
		}
		else
		{
			int x[5] = { 307,229,94,94,205 };
			int y[5] = { 1289,1182,1176,1296,1335 };

			//分别在5个地方召唤雷诺
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					summonShip(x[i], y[i]);
				}
			}
			sendKey(VK_ESCAPE);
			quitBattleSuccess();
		}

		Sleep(100);

		setCursor(308, 1132);
		while (!(Color::getPixel(469, 1091) == Color(254, 254, 254)))
		{
			sendClick();
			Sleep(100);
		}
	}

private:

	//检测是否有极性因子 为了不出错 检查两遍
	bool checkFactors()
	{
		for (int i = 0; i < 2; i++)
		{
			if (Color::getPixel(2515, 535) == Color(188, 62, 70))
			{
				return true;
			}

			if (Color::getPixel(2515, 625) == Color(188, 62, 70))
			{
				return true;
			}

			if (Color::getPixel(2515, 715) == Color(188, 62, 70))
			{
				return true;
			}

			if (Color::getPixel(2515, 805) == Color(188, 62, 70))
			{
				return true;
			}
		}
		return false;
	}

	//召唤雷诺
	void summonShip(int x,int y)
	{
		setCursor(x, y);
		keybd_event(VK_LCONTROL, 0, 0, 0);
		keybd_event('Z', 0, 0, 0);
		sendClick();
		keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event('Z', 0, KEYEVENTF_KEYUP, 0);
		Sleep(20);
	}

	//正常结束战斗
	void quitBattleSuccess()
	{
		setCursor(1272, 881);
		waitForColor(1472, 888, Color(0, 254, 136));
		sendClick();
	}

	void waitForColor(int x, int y, const Color& c)
	{
		while (!(Color::getPixel(x, y) == c))
		{
			Sleep(100);
		}
		Sleep(100);
	}

	void sendKey(BYTE bVk)
	{
		keybd_event(bVk, 0, 0, 0);
		keybd_event(bVk, 0, KEYEVENTF_KEYUP, 0);
		Sleep(20);
	}

	void setCursor(int x, int y)
	{
		SetCursorPos(x, y);
		Sleep(20);
	}

	void sendClick()
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(20);
	}

};