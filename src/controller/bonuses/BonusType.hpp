/**
 * @file BonusType.hpp
 * @brief Énumère les types de bonus disponibles.
 */
#pragma once

/**
 * @enum BonusType
 * @brief Types sémantiques de bonus pouvant exister dans le jeu.
 */
enum class BonusType {
    ENLARGE,
    LASER,
    CATCH,
    EXTRA_LIFE,
    SLOW_BALL,
    SPLIT
};