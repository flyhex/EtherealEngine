////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "RenderWindow.h"
#include "RenderSurface.h"

void RenderWindow::onResize()
{
	prepareSurface();
	auto size = getSize();
	onResized(*this, size);
}

void RenderWindow::onClose()
{
	onClosed(*this);
}

RenderWindow::RenderWindow()
{
	mSurface = std::make_shared<RenderSurface>();
}

RenderWindow::RenderWindow(sf::VideoMode mode, const std::string& title, std::uint32_t style /*= sf::Style::Default*/) : sf::Window(mode, title, style)
{
	mSurface = std::make_shared<RenderSurface>();
}

RenderWindow::~RenderWindow()
{
	if (mSurface)
	{
		mSurface.reset();
		gfx::frame();
		gfx::frame();
	}
	
}

bool RenderWindow::filterEvent(const sf::Event& event)
{
	mInput.handleEvent(event);
	return sf::Window::filterEvent(event);;
}

void RenderWindow::frameBegin()
{
	RenderSurface::pushSurface(mSurface);
	mSurface->clear();
	mInput.update();
}

void RenderWindow::frameUpdate(float dt)
{
}

void RenderWindow::frameEnd()
{
	RenderSurface::popSurface();
}

void RenderWindow::frameRender()
{
}

void RenderWindow::prepareSurface()
{
	auto size = getSize();
	if (mIsMain)
	{
		gfx::reset(size.width, size.height, 0);
		mSurface->setSize(size);
	}
	else
	{
		mSurface->populate(getSystemHandle(), size.width, size.height);
	}

}

void RenderWindow::delayedClose()
{
	onClose();
}
