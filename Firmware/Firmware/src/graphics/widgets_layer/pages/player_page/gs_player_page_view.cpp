#include "gs_player_page_view.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "IconFont24px.hpp"
#include "PlayerIcons68px.hpp"

namespace Graphics::Views
{

PlayerPage::PlayerPage( const Theme::IThemeController* _themeController )
	:	PageViewObject<IPlayerWatchPage>{ _themeController, IPlayerWatchPage::PlayerPageName }
{
	initStyles();
}

void PlayerPage::show()
{
	PageViewObject::show();

	auto parent = lv_disp_get_scr_act( nullptr );

	auto pThemeProvider = PageViewObject::getThemeController();
	if (!pThemeProvider )
		return;

	const std::uint32_t DisplayWidth { pThemeProvider->getDisplayWidth() };
	const std::uint32_t DisplayHeight { pThemeProvider->getDisplayHeight() };

	initPageTitle( parent, DisplayWidth, DisplayHeight );
	initPlayIcon( parent, DisplayWidth, DisplayHeight );
	initPrevSongIcon( parent, DisplayWidth, DisplayHeight );
	initNextSongIcon( parent, DisplayWidth, DisplayHeight );
}

void PlayerPage::hide()
{
	PageViewObject::hide();

	Meta::tupleApply(
			[]( auto&& _nodeToReset ){ _nodeToReset.reset(); }
		,	std::forward_as_tuple(
				m_pageTitle
			,	m_melodyIcon
			,	m_pPlayIconFirst
			,	m_pPlayIconSecond
			,	m_pSwitchPreviousSongArrow
			,	m_pSwitchPreviousSongLine
			,	m_pSwitchNextSongArrow
			,	m_pSwitchNextSongLine
		)
	);
}

void PlayerPage::reloadStyle()
{
	PageViewObject::reloadStyle();
	initStyles();
}

void PlayerPage::setPause()
{
}

void PlayerPage::setPlaying()
{
}

void PlayerPage::initStyles()
{
	auto pThemeProvider = PageViewObject::getThemeController();
	if (!pThemeProvider )
		return;

	m_mainLabelStyleDark = pThemeProvider->getFontStyle(
			Theme::FontSize::below_normal
		,	Theme::Color::MainThemeDark
	);

	m_melodyIconStyle = m_playIconStyleDark = pThemeProvider->getIconsFont(
			Theme::FontSize::below_normal
		,	Theme::Color::MainThemeDark
	);

	m_playIconStyleDark = pThemeProvider->getIconsFont(
			Theme::FontSize::large
		,	Theme::Color::MainThemeDark
	);
	m_playIconStyleLight = pThemeProvider->getIconsFont(
			Theme::FontSize::large
		,	Theme::Color::MainThemeLight
	);

}

void PlayerPage::initPageTitle(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
	)
{
	m_pageTitle.reset( lv_label_create( _parentObject, nullptr ) );

	lv_label_set_style( m_pageTitle.get(), LV_LABEL_STYLE_MAIN, &m_mainLabelStyleDark );
	lv_label_set_text( m_pageTitle.get(), "MUSIC" );
	lv_obj_align(
			m_pageTitle.get()
		,	nullptr
		,	LV_ALIGN_IN_TOP_MID
		,	0
		,	_displayHeight / 6
	);

	m_melodyIcon.reset( lv_label_create( _parentObject, nullptr ) );

	lv_label_set_style( m_melodyIcon.get(), LV_LABEL_STYLE_MAIN, &m_melodyIconStyle );
	lv_label_set_text( m_melodyIcon.get(), IconFontSymbols::Music::Melody.data() );
	lv_obj_align(
			m_melodyIcon.get()
		,	nullptr
		,	LV_ALIGN_IN_TOP_MID
		,	0
		,	_displayHeight / 30
	);
}

void PlayerPage::initPlayIcon(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
	)
{

	m_pPlayIconSecond.reset( lv_label_create( _parentObject, nullptr ) );

	lv_label_set_style( m_pPlayIconSecond.get(), LV_LABEL_STYLE_MAIN, &m_playIconStyleLight );
	lv_label_set_text( m_pPlayIconSecond.get(), IconFontSymbols::Player::SecondPart.data() );
	lv_obj_align(
		m_pPlayIconSecond.get()
		,	nullptr
		,	LV_ALIGN_CENTER
		,	6
		,	0
	);

	m_pPlayIconFirst.reset( lv_label_create( _parentObject, nullptr ) );

	lv_label_set_style( m_pPlayIconFirst.get(), LV_LABEL_STYLE_MAIN, &m_playIconStyleDark );
	lv_label_set_text( m_pPlayIconFirst.get(), IconFontSymbols::Player::FirstPart.data() );
	lv_obj_align(
			m_pPlayIconFirst.get()
		,	nullptr
		,	LV_ALIGN_IN_LEFT_MID
		,	_displayWidth / 3 +  _displayWidth / 25
		,	0
	);
}

void PlayerPage::initNextSongIcon(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
	)
{
	m_pSwitchNextSongArrow.reset( lv_label_create( _parentObject, nullptr ) );

	lv_label_set_style(m_pSwitchNextSongArrow.get(), LV_LABEL_STYLE_MAIN, &m_playIconStyleLight );
	lv_label_set_text(m_pSwitchNextSongArrow.get(), IconFontSymbols::Player::ArrowRight.data() );
	lv_obj_align(
			m_pSwitchNextSongArrow.get()
		,	nullptr
		,	LV_ALIGN_CENTER
		,	_displayWidth / 3
		,	0
	);

	m_pSwitchNextSongLine.reset(lv_label_create(_parentObject, nullptr ) );

	lv_label_set_style(m_pSwitchNextSongLine.get(), LV_LABEL_STYLE_MAIN, &m_playIconStyleLight );
	lv_label_set_text(m_pSwitchNextSongLine.get(), IconFontSymbols::Player::Line.data() );
	lv_obj_align(
			m_pSwitchNextSongLine.get()
		,	nullptr
		,	LV_ALIGN_CENTER
		,	_displayWidth / 5
		,	0
	);
}

void PlayerPage::initPrevSongIcon(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
	)
{
	m_pSwitchPreviousSongArrow.reset( lv_label_create( _parentObject, nullptr ) );

	lv_label_set_style( m_pSwitchPreviousSongArrow.get(), LV_LABEL_STYLE_MAIN, &m_playIconStyleDark );
	lv_label_set_text(m_pSwitchPreviousSongArrow.get(), IconFontSymbols::Player::ArrowLeft.data() );
	lv_obj_align(
			m_pSwitchPreviousSongArrow.get()
		,	nullptr
		,	LV_ALIGN_IN_LEFT_MID
		,	_displayWidth / 20
		,	0
	);

	m_pSwitchPreviousSongLine.reset(lv_label_create(_parentObject, nullptr ) );

	lv_label_set_style(m_pSwitchPreviousSongLine.get(), LV_LABEL_STYLE_MAIN, &m_playIconStyleDark );
	lv_label_set_text(m_pSwitchPreviousSongLine.get(), IconFontSymbols::Player::Line.data() );
	lv_obj_align(
			m_pSwitchPreviousSongLine.get()
		,	nullptr
		,	LV_ALIGN_IN_LEFT_MID
		,	_displayWidth / 10
		,	0
	);
}

std::unique_ptr<IPlayerWatchPage>
createPlayerWatchView( const Theme::IThemeController* _themeController )
{
	return std::make_unique<PlayerPage>( _themeController );
}

}