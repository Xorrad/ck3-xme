#include "Title.hpp"

Title::Title() : Title("", sf::Color(0, 0, 0)) {}

Title::Title(std::string name, sf::Color color) : m_Name(name), m_Color(color) {}

// Title::Title(const Title& title) : Title(title.GetName(), title.GetColor()) {}

std::string Title::GetName() const {
    return m_Name;
}

sf::Color Title::GetColor() const {
    return m_Color;
}

SharedPtr<HighTitle>& Title::GetLiegeTitle() {
    return m_LiegeTitle;
}

bool Title::Is(TitleType type) const {
    return this->GetType() == type;
}

void Title::SetName(std::string name) {
    m_Name = name;
}

void Title::SetColor(sf::Color color) {
    m_Color = color;
}

void Title::SetLiegeTitle(SharedPtr<HighTitle> title) {
    m_LiegeTitle = title;
}

HighTitle::HighTitle() : Title("", sf::Color(0, 0, 0)) {}

HighTitle::HighTitle(std::string name, sf::Color color) : Title(name, color) {}

// HighTitle::~HighTitle() {
//     m_DejureTitles.clear();
//     m_CapitalTitle
// }

std::vector<SharedPtr<Title>>& HighTitle::GetDejureTitles() {
    return m_DejureTitles;
}

SharedPtr<CountyTitle>& HighTitle::GetCapitalTitle() {
    return m_CapitalTitle;
}

void HighTitle::AddDejureTitle(SharedPtr<Title> title) {
    if(title == nullptr)
        return;
    m_DejureTitles.push_back(title);

    SharedPtr<HighTitle> previousLiege = title->GetLiegeTitle();
    if(previousLiege != nullptr) {
        previousLiege->RemoveDejureTitle(title);
    }
    title->SetLiegeTitle(shared_from_this());
}

void HighTitle::RemoveDejureTitle(SharedPtr<Title> title) {
    if(title == nullptr)
        return;
    m_DejureTitles.erase(std::remove(m_DejureTitles.begin(), m_DejureTitles.end(), title), m_DejureTitles.end());
    title->SetLiegeTitle(nullptr);
}

void HighTitle::SetCapitalTitle(SharedPtr<CountyTitle> title) {
    m_CapitalTitle = title;
}

BaronyTitle::BaronyTitle() : Title() {}
BaronyTitle::BaronyTitle(std::string name, sf::Color color) : Title(name, color) {}
BaronyTitle::BaronyTitle(std::string name, sf::Color color, int provinceId) : Title(name, color), m_ProvinceId(provinceId) {}

TitleType BaronyTitle::GetType() const {
    return TitleType::BARONY;
}

int BaronyTitle::GetProvinceId() const {
    return m_ProvinceId;
}

void BaronyTitle::SetProvinceId(int id) {
    m_ProvinceId = id;
}

CountyTitle::CountyTitle() : HighTitle() {}
CountyTitle::CountyTitle(std::string name, sf::Color color) : HighTitle(name, color) {}

TitleType CountyTitle::GetType() const {
    return TitleType::COUNTY;
}

DuchyTitle::DuchyTitle() : HighTitle() {}
DuchyTitle::DuchyTitle(std::string name, sf::Color color) : HighTitle(name, color) {}

TitleType DuchyTitle::GetType() const {
    return TitleType::DUCHY;
}

KingdomTitle::KingdomTitle() : HighTitle() {}
KingdomTitle::KingdomTitle(std::string name, sf::Color color) : HighTitle(name, color) {}

TitleType KingdomTitle::GetType() const {
    return TitleType::KINGDOM;
}

EmpireTitle::EmpireTitle() : HighTitle() {}
EmpireTitle::EmpireTitle(std::string name, sf::Color color) : HighTitle(name, color) {}

TitleType EmpireTitle::GetType() const {
    return TitleType::EMPIRE;
}