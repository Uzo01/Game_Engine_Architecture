/** \file graphicsContext */
#pragma once

namespace Engine
{
	class GraphicsContext
	{
	public:
		virtual void init() = 0;//!< create initialise
		virtual void swapBuffer() = 0;//!< Swap buffer
		
	private:
	};

}
