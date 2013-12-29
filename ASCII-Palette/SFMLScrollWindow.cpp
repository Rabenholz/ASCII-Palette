#include "StdAfx.h"
#include "SFMLScrollWindow.h"

const float SFMLScrollWindow::kScrollbarWidth = 15.0f;

SFMLScrollWindow::SFMLScrollWindow(const sf::Window& window, const sf::Vector2f& size)
	:SFMLGUIElement(window),
	 m_child(nullptr),
	 m_innerRect(size),
	 m_rectangle(sf::Vector2f(size.x + kScrollbarWidth, size.y)),
	 m_verticalScrollbar(sf::Vector2f(kScrollbarWidth, size.y)),
	 m_verticalScrollbarVisibility(true),
	 m_horizontalScrollbarVisibility(false),
	 m_verticalScrollEnabled(false),
	 m_verticalScrollYBegin(0.f),
	 m_stickyBottom(true),
	 m_atBottom(false)
{
	//testing
	m_rectangle.setFillColor(sf::Color::White);
	m_rectangle.setOutlineThickness(1.f);
	m_rectangle.setOutlineColor(sf::Color::Blue);

	m_verticalScrollbar.setPosition(size.x, 0.f);
	m_verticalScrollbar.setFillColor(sf::Color(200,200,200));


	addMouseRolloverFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::updateScrollbarHighlight));
	addMouseLeftPressedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::beginVerticalScroll));
	addGlobalMouseLeftReleasedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::endVerticalScroll));

	addMouseLeftPressedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildMouseLeftPressed));
	addMouseLeftReleasedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildMouseLeftReleased));
	addMouseRightPressedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildMouseRightPressed));
	addMouseRightReleasedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildMouseRightReleased));
	addMouseMiddlePressedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildMouseMiddlePressed));
	addMouseMiddleReleasedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildMouseMiddleReleased));
	addMouseLeftClickedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildMouseLeftReleased));
	addMouseRightClickedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildMouseRightReleased));
	addMouseMiddleClickedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildMouseMiddleReleased));
	addMouseRolloverFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildMouseRollover));
	addGlobalMouseLeftReleasedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildGlobalMouseLeftReleased));
	addGlobalMouseRightReleasedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildGlobalMouseRightReleased));
	addGlobalMouseMiddleReleasedFunction(std::make_shared<TFunctor<SFMLScrollWindow>>(this,&SFMLScrollWindow::OnChildGlobalMouseMiddleReleased));
}


SFMLScrollWindow::~SFMLScrollWindow(void)
{
}

void SFMLScrollWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	//testing
	target.draw(m_rectangle, states);
	target.draw(m_verticalScrollbar, states);
	//
	if(m_child)
	{
		sf::FloatRect gBounds = getTransform().transformRect(sf::FloatRect(sf::Vector2f(0,0), m_innerRect.getSize()));
		sf::Vector2f windowSize(static_cast<float>(target.getSize().x), static_cast<float>(target.getSize().y));
		sf::FloatRect viewport(gBounds.left/windowSize.x, gBounds.top/windowSize.y, gBounds.width/windowSize.x, gBounds.height/windowSize.y);
		
		sf::View oldView(target.getView());
		sf::View clippedView(gBounds);
		clippedView.setViewport(viewport);
		target.setView(clippedView);
		m_child->draw(target, states);
		target.setView(oldView);
		//if(getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y)))
		//	target.draw(m_charMagnify, states);
	}
}

void SFMLScrollWindow::update()
{
	m_child->setGlobalOffset(sf::Vector2f(getPosition().x + getGlobalOffset().x, getPosition().y + getGlobalOffset().y));
	if(m_child)
	{
		float vertBarHeight = m_innerRect.getSize().y;
		if(m_child->getLocalBounds().height > m_innerRect.getSize().y)
		{
			vertBarHeight = (m_innerRect.getSize().y / m_child->getLocalBounds().height) * m_innerRect.getSize().y;
		}

		m_verticalScrollbar.setSize(sf::Vector2f(kScrollbarWidth, vertBarHeight));
	}
	else
	{
		m_verticalScrollbar.setSize(sf::Vector2f(kScrollbarWidth, m_innerRect.getSize().y));
	}
	if(m_verticalScrollEnabled)
		updateVerticalScroll();
	else if(m_stickyBottom)
	{
		if(m_child->getLocalBounds().height < m_innerRect.getLocalBounds().height)
		{
			m_atBottom = true;
			m_child->setPosition(0.f, 0.f);
			m_verticalScrollbar.setPosition(m_innerRect.getSize().x, 0.f);
		}
		else if(m_atBottom)
		{
			m_child->setPosition(0.f, -(m_child->getLocalBounds().height - m_innerRect.getSize().y));
			m_verticalScrollbar.setPosition(m_innerRect.getSize().x, m_innerRect.getSize().y - m_verticalScrollbar.getSize().y);
		}
	}
	if(m_child->getLocalBounds().height > m_innerRect.getLocalBounds().height && m_child->getPosition().y*-1 > m_child->getLocalBounds().height - m_innerRect.getSize().y)
	{
		m_child->setPosition(0.f, -(m_child->getLocalBounds().height - m_innerRect.getSize().y));
		m_verticalScrollbar.setPosition(m_innerRect.getSize().x, m_innerRect.getSize().y - m_verticalScrollbar.getSize().y);
	}
}

sf::FloatRect SFMLScrollWindow::getLocalBounds(void) const
{
	return m_rectangle.getLocalBounds();
}

sf::FloatRect SFMLScrollWindow::getGlobalBounds(void) const
{
	sf::Transform transform = getTransform();
	return transform.translate(getGlobalOffset()).transformRect(m_rectangle.getGlobalBounds());
}

void SFMLScrollWindow::setChild(std::unique_ptr<SFMLGUIElement> child)
{
	m_child = std::move(child);
	m_child->setGlobalOffset(sf::Vector2f(getPosition().x + getGlobalOffset().x, getPosition().y + getGlobalOffset().y));
}

SFMLGUIElement* SFMLScrollWindow::getChild() const
{
	return m_child.get();
}

void SFMLScrollWindow::setVerticalScrollbarVisibility(bool b)
{
	m_verticalScrollbarVisibility = b;

	m_rectangle.setSize(sf::Vector2f(m_innerRect.getSize().x + (kScrollbarWidth*m_verticalScrollbarVisibility), m_innerRect.getSize().y + (kScrollbarWidth*m_horizontalScrollbarVisibility)));
}

void SFMLScrollWindow::setHorizontalScrollbarVisibility(bool b)
{
	m_horizontalScrollbarVisibility = b;

	m_rectangle.setSize(sf::Vector2f(m_innerRect.getSize().x + (kScrollbarWidth*m_verticalScrollbarVisibility), m_innerRect.getSize().y + (kScrollbarWidth*m_horizontalScrollbarVisibility)));
}

void SFMLScrollWindow::setStickyBottom(bool b)
{
	m_stickyBottom = b;
}

bool SFMLScrollWindow::getVerticalScrollbarVisibility() const
{
	return m_verticalScrollbarVisibility;
}
bool SFMLScrollWindow::getHorizontalScrollbarVisibility() const
{
	return m_horizontalScrollbarVisibility;
}

bool SFMLScrollWindow::getStickyBottom() const
{
	return m_stickyBottom;
}

void SFMLScrollWindow::updateScrollbarHighlight()
{
	//vertical
	if(m_verticalScrollbarVisibility)
	{
		if(m_verticalScrollEnabled || getTransform().transformRect(m_verticalScrollbar.getGlobalBounds()).contains(static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y)))
		{
			m_verticalScrollbar.setFillColor(sf::Color(150,150,150));
		}
		else
		{
			m_verticalScrollbar.setFillColor(sf::Color(200,200,200));
		}
	}
	//horizontal
}

void SFMLScrollWindow::beginVerticalScroll()
{
	m_verticalScrollYBegin = static_cast<float>(getLocalPoint(sf::Mouse::getPosition(m_window)).y) - m_verticalScrollbar.getPosition().y;
	m_verticalScrollEnabled = true;
}

void SFMLScrollWindow::updateVerticalScroll()
{
	float scrollY = static_cast<float>(getLocalPoint(sf::Mouse::getPosition(m_window)).y) - m_verticalScrollYBegin;
	scrollY = std::max(0.f, scrollY);
	scrollY = std::min(m_innerRect.getSize().y - m_verticalScrollbar.getSize().y, scrollY);
	m_verticalScrollbar.setPosition(m_innerRect.getSize().x, scrollY);
	float scrollPercent = scrollY/(m_innerRect.getSize().y - m_verticalScrollbar.getSize().y);
	if(m_child->getLocalBounds().height > m_innerRect.getLocalBounds().height)
		m_child->setPosition(0.f, -scrollPercent * (m_child->getLocalBounds().height - m_innerRect.getSize().y));
	else
		m_child->setPosition(0.f, 0.f);

	m_atBottom = (scrollPercent > 0.99f || m_child->getLocalBounds().height < m_innerRect.getLocalBounds().height);
}

void SFMLScrollWindow::endVerticalScroll()
{
	m_verticalScrollEnabled = false;
	m_verticalScrollbar.setFillColor(sf::Color(200,200,200));
}

bool SFMLScrollWindow::inInnerRect(const sf::Vector2f& point) const
{
	return getTransform().transformRect(m_innerRect.getGlobalBounds()).contains(point);
}
bool SFMLScrollWindow::inInnerRect(const sf::Vector2i& point) const
{
	return getTransform().transformRect(m_innerRect.getGlobalBounds()).contains(sf::Vector2f(static_cast<float>(point.x), static_cast<float>(point.y)));
}

bool SFMLScrollWindow::mouseInInnerRect() const
{
	return inInnerRect(sf::Mouse::getPosition(m_window));
}

//forward events if in inner rect
void SFMLScrollWindow::OnChildMouseLeftPressed()
{
	if(m_child && mouseInInnerRect())
	{
		m_child->OnMouseLeftPressed();
	}
}

void SFMLScrollWindow::OnChildMouseLeftReleased()
{
	if(m_child && mouseInInnerRect())
	{
		m_child->OnMouseLeftReleased();
	}
}

void SFMLScrollWindow::OnChildMouseRightPressed()
{
	if(m_child && mouseInInnerRect())
	{
		m_child->OnMouseRightPressed();
	}
}

void SFMLScrollWindow::OnChildMouseRightReleased()
{
	if(m_child && mouseInInnerRect())
	{
		m_child->OnMouseRightReleased();
	}
}

void SFMLScrollWindow::OnChildMouseMiddlePressed()
{
	if(m_child && mouseInInnerRect())
	{
		m_child->OnMouseMiddlePressed();
	}
}

void SFMLScrollWindow::OnChildMouseMiddleReleased()
{
	if(m_child && mouseInInnerRect())
	{
		m_child->OnMouseMiddleReleased();
	}
}

void SFMLScrollWindow::OnChildMouseRollover()
{
	if(m_child && mouseInInnerRect())
	{
		m_child->OnMouseRollover();
	}
}

void SFMLScrollWindow::OnChildGlobalMouseLeftReleased()
{
	if(m_child)
	{
		m_child->OnGlobalMouseLeftReleased();
	}
}

void SFMLScrollWindow::OnChildGlobalMouseRightReleased()
{
	if(m_child)
	{
		m_child->OnGlobalMouseRightReleased();
	}
}

void SFMLScrollWindow::OnChildGlobalMouseMiddleReleased()
{
	if(m_child)
	{
		m_child->OnGlobalMouseMiddleReleased();
	}
}