#pragma once

#include <Color.h>
#include <ToolboxWidget.h>

class SkillbarWidget final : public ToolboxWidget
{
    SkillbarWidget()
    {
        is_resizable = false;
    };
    ~SkillbarWidget(){};

public:
    static SkillbarWidget &Instance()
    {
        static SkillbarWidget instance;
        return instance;
    }

    const char *Name() const override
    {
        return "Skillbar";
    }

    void LoadSettings(CSimpleIni *ini) override;
    void SaveSettings(CSimpleIni *ini) override;
    void DrawSettingInternal() override;

    // Draw user interface. Will be called every frame if the element is visible
    void Draw(IDirect3DDevice9 *pDevice) override;

private:
    struct Skill
    {
        std::array<char, 16> cooldown{};
        Color color{};
        std::vector<std::pair<std::array<char, 16>, Color>> effects{};
    };

    std::array<Skill, 8> m_skills{};
    Color color_text{};
    Color color_border{};
    Color color_long{};
    Color color_medium{};
    Color color_short{};

    clock_t medium_treshold{5000};
    clock_t short_treshold{2500};

    int m_skill_width = 50;
    int m_skill_height = 50;
    GuiUtils::FontSize m_font_size = GuiUtils::FontSize::f16;
    int m_effect_offset = -100;
    bool vertical = false;
    bool display_effect_times = false;

    Color UptimeToColor(clock_t uptime) const;
};
