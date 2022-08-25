#pragma once

#include"Color.h"

//���Էֱ��� 2560 1440

//������Ϣ�����ж���Ϸ״̬ ������ ս�� �������ȵ�
//���˵����� 469 1091 254 254 254
//ս������ 1231 81 68 156 100
//����ɹ� 1472 888 0 254 136

//׼����Ϸ��ťλ�� 267 1268
//���㰴ťλ�� 308 1132


//��������Ƭλ��
//307 1289
//229 1182
//94 1176
//94 1296
//205 1335

//�������� 188 62 70
//0 2515 535
//1 2515 625
//2 2515 715
//3 2515 805

class Script
{
public:

	//�ű��Զ���һ��
	void start()
	{
		//��ʼ����
		waitForColor(469, 1091, Color(254, 254, 254));
		setCursor(267, 1268);
		sendClick();

		//�ȴ�ս��
		waitForColor(1231, 81, Color(68, 156, 100));
		//ͻ�������п��ܻ����������Եõ�һ��
		Sleep(500);

		bool hasFactor = checkFactors();

		//�ֱ���һ���Ƿ��м�������
		if (hasFactor)
		{
			sendKey(VK_F10);
			sendKey('Q');
		}
		else
		{
			int x[5] = { 307,229,94,94,205 };
			int y[5] = { 1289,1182,1176,1296,1335 };

			//�ֱ���5���ط��ٻ���ŵ
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

	//����Ƿ��м������� Ϊ�˲����� �������
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

	//�ٻ���ŵ
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

	//��������ս��
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