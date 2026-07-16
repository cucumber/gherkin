#include "cucumber/gherkin/dialect.hpp"

namespace cucumber::gherkin {

    const keywords_maps& all_keywords()
    {
        static const keywords_maps kwms = {
        {
                "af",
                {
                    { "and", { "* ", "En " } },
                    { "background", { "Agtergrond" } },
                    { "but", { "* ", "Maar " } },
                    { "examples", { "Voorbeelde" } },
                    { "feature", { "Funksie", "Besigheid Behoefte", "Vermoë" } },
                    { "given", { "* ", "Gegewe " } },
                    { "rule", { "Reël", "Reel" } },
                    { "scenario", { "Voorbeeld", "Situasie" } },
                    { "scenarioOutline", { "Situasie Uiteensetting" } },
                    { "then", { "* ", "Dan " } },
                    { "when", { "* ", "Wanneer " } }
                }
            },
        {
                "am",
                {
                    { "and", { "* ", "Եվ " } },
                    { "background", { "Կոնտեքստ" } },
                    { "but", { "* ", "Բայց " } },
                    { "examples", { "Օրինակներ" } },
                    { "feature", { "Ֆունկցիոնալություն", "Հատկություն" } },
                    { "given", { "* ", "Դիցուք " } },
                    { "rule", { "Rule" } },
                    { "scenario", { "Օրինակ", "Սցենար" } },
                    { "scenarioOutline", { "Սցենարի կառուցվացքը" } },
                    { "then", { "* ", "Ապա " } },
                    { "when", { "* ", "Եթե ", "Երբ " } }
                }
            },
        {
                "an",
                {
                    { "and", { "* ", "Y ", "E " } },
                    { "background", { "Antecedents" } },
                    { "but", { "* ", "Pero " } },
                    { "examples", { "Eixemplos" } },
                    { "feature", { "Caracteristica" } },
                    { "given", { "* ", "Dau ", "Dada ", "Daus ", "Dadas " } },
                    { "rule", { "Rule" } },
                    { "scenario", { "Eixemplo", "Caso" } },
                    { "scenarioOutline", { "Esquema del caso" } },
                    { "then", { "* ", "Alavez ", "Allora ", "Antonces " } },
                    { "when", { "* ", "Cuan " } }
                }
            },
        {
                "ar",
                {
                    { "and", { "* ", "و " } },
                    { "background", { "الخلفية" } },
                    { "but", { "* ", "لكن " } },
                    { "examples", { "امثلة" } },
                    { "feature", { "خاصية" } },
                    { "given", { "* ", "بفرض " } },
                    { "rule", { "Rule" } },
                    { "scenario", { "مثال", "سيناريو" } },
                    { "scenarioOutline", { "سيناريو مخطط" } },
                    { "then", { "* ", "اذاً ", "ثم " } },
                    { "when", { "* ", "متى ", "عندما " } }
                }
            },
        {
                "ast",
                {
                    { "and", { "* ", "Y ", "Ya " } },
                    { "background", { "Antecedentes" } },
                    { "but", { "* ", "Peru " } },
                    { "examples", { "Exemplos" } },
                    { "feature", { "Carauterística" } },
                    { "given", { "* ", "Dáu ", "Dada ", "Daos ", "Daes " } },
                    { "rule", { "Rule" } },
                    { "scenario", { "Exemplo", "Casu" } },
                    { "scenarioOutline", { "Esbozu del casu" } },
                    { "then", { "* ", "Entós " } },
                    { "when", { "* ", "Cuando " } }
                }
            },
        {
                "az",
                {
                    { "and", { "* ", "Və ", "Həm " } },
                    { "background", { "Keçmiş", "Kontekst" } },
                    { "but", { "* ", "Amma ", "Ancaq " } },
                    { "examples", { "Nümunələr" } },
                    { "feature", { "Özəllik" } },
                    { "given", { "* ", "Tutaq ki ", "Verilir " } },
                    { "rule", { "Rule" } },
                    { "scenario", { "Nümunə", "Ssenari" } },
                    { "scenarioOutline", { "Ssenarinin strukturu" } },
                    { "then", { "* ", "O halda " } },
                    { "when", { "* ", "Əgər ", "Nə vaxt ki " } }
                }
            },
        {
                "be",
                {
                    { "and", { "* ", "I ", "Ды ", "Таксама " } },
                    { "background", { "Кантэкст" } },
                    { "but", { "* ", "Але ", "Інакш " } },
                    { "examples", { "Прыклады" } },
                    { "feature", { "Функцыянальнасць", "Фіча" } },
                    { "given", { "* ", "Няхай ", "Дадзена " } },
                    { "rule", { "Правілы" } },
                    { "scenario", { "Сцэнарый", "Cцэнар" } },
                    { "scenarioOutline", { "Шаблон сцэнарыя", "Узор сцэнара" } },
                    { "then", { "* ", "Тады " } },
                    { "when", { "* ", "Калі " } }
                }
            },
        {
                "bg",
                {
                    { "and", { "* ", "И " } },
                    { "background", { "Предистория" } },
                    { "but", { "* ", "Но " } },
                    { "examples", { "Примери" } },
                    { "feature", { "Функционалност" } },
                    { "given", { "* ", "Дадено " } },
                    { "rule", { "Правило" } },
                    { "scenario", { "Пример", "Сценарий" } },
                    { "scenarioOutline", { "Рамка на сценарий" } },
                    { "then", { "* ", "То " } },
                    { "when", { "* ", "Когато " } }
                }
            },
        {
                "bm",
                {
                    { "and", { "* ", "Dan " } },
                    { "background", { "Latar Belakang" } },
                    { "but", { "* ", "Tetapi ", "Tapi " } },
                    { "examples", { "Contoh" } },
                    { "feature", { "Fungsi" } },
                    { "given", { "* ", "Diberi ", "Bagi " } },
                    { "rule", { "Rule" } },
                    { "scenario", { "Senario", "Situasi", "Keadaan" } },
                    { "scenarioOutline", { "Kerangka Senario", "Kerangka Situasi", "Kerangka Keadaan", "Garis Panduan Senario" } },
                    { "then", { "* ", "Maka ", "Kemudian " } },
                    { "when", { "* ", "Apabila " } }
                }
            },
        {
                "bs",
                {
                    { "and", { "* ", "I ", "A " } },
                    { "background", { "Pozadina" } },
                    { "but", { "* ", "Ali " } },
                    { "examples", { "Primjeri" } },
                    { "feature", { "Karakteristika" } },
                    { "given", { "* ", "Dato " } },
                    { "rule", { "Rule" } },
                    { "scenario", { "Primjer", "Scenariju", "Scenario" } },
                    { "scenarioOutline", { "Scenariju-obris", "Scenario-outline" } },
                    { "then", { "* ", "Zatim " } },
                    { "when", { "* ", "Kada " } }
                }
            },
        {
                "ca",
                {
                    { "and", { "* ", "I " } },
                    { "background", { "Rerefons", "Antecedents" } },
                    { "but", { "* ", "Però " } },
                    { "examples", { "Exemples" } },
                    { "feature", { "Característica", "Funcionalitat" } },
                    { "given", { "* ", "Donat ", "Donada ", "Atès ", "Atesa " } },
                    { "rule", { "Rule" } },
                    { "scenario", { "Exemple", "Escenari" } },
                    { "scenarioOutline", { "Esquema de l'escenari" } },
                    { "then", { "* ", "Aleshores ", "Cal " } },
                    { "when", { "* ", "Quan " } }
                }
            },
        {
                "cs",
                {
                    { "and", { "* ", "A také ", "A " } },
                    { "background", { "Pozadí", "Kontext" } },
                    { "but", { "* ", "Ale " } },
                    { "examples", { "Příklady" } },
                    { "feature", { "Požadavek" } },
                    { "given", { "* ", "Pokud ", "Za předpokladu " } },
                    { "rule", { "Pravidlo" } },
                    { "scenario", { "Příklad", "Scénář" } },
                    { "scenarioOutline", { "Náčrt Scénáře", "Osnova scénáře" } },
                    { "then", { "* ", "Pak " } },
                    { "when", { "* ", "Když " } }
                }
            }
        };

        return kwms;
    }

    const keywords_map& keywords(const std::string_view& language)
    {
        return all_keywords().at(language);
    }
}