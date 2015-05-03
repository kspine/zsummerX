﻿/*
* zsummerX License
* -----------
* 
* zsummerX is licensed under the terms of the MIT license reproduced below.
* This means that zsummerX is free software and can be used for both academic
* and commercial purposes at absolutely no cost.
* 
* 
* ===============================================================================
* 
* Copyright (C) 2010-2015 YaweiZhang <yawei.zhang@foxmail.com>.
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
* 
* ===============================================================================
* 
* (end of COPYRIGHT)
*/

#ifndef _ZSUMMER_EPOLL_IMPL_H_
#define _ZSUMMER_EPOLL_IMPL_H_
#include "common_impl.h"
#include "../timer/timer.h"

namespace zsummer
{
	namespace network
	{
		class EventLoop : public std::enable_shared_from_this<EventLoop>
		{
		public:
			typedef std::vector<void*> MessageStack;
			EventLoop(){}
			~EventLoop(){}
			bool initialize();
			void runOnce(bool isImmediately = false);

			template <typename handle>
			inline void post(handle &&h){PostMessage(std::move(h));}
			inline unsigned long long createTimer(unsigned int delayms, _OnTimerHandler &&handle){return _timer.createTimer(delayms, std::move(handle));}
			inline bool cancelTimer(unsigned long long timerID){return _timer.cancelTimer(timerID);}

		public:
			bool registerEvent(int op, tagRegister &reg);
			void PostMessage(_OnPostHandler &&handle);
		private:
			std::string logSection();
		private:
			int	_epoll = InvalideFD;
			epoll_event _events[5000] = {};
			int		_sockpair[2] = {};
			tagRegister _register;
			MessageStack _stackMessages;
			std::mutex	 _stackMessagesLock;
			Timer _timer;
		};
		typedef std::shared_ptr<EventLoop> EventLoopPtr;
	}

}





















#endif











