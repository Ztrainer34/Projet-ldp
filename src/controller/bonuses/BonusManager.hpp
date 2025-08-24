/**
 * @file BonusManager.hpp
 * @brief Déclare le gestionnaire centralisé des bonus et capsules.
 */
#ifndef BONUSMANAGER_HPP
#define BONUSMANAGER_HPP

#include <vector>
#include <memory>
#include "../../model/Capsule.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"
#include "../../model/Block.hpp"
#include "../GameContext.hpp"
#include "Bonus.hpp"

/**
 * @class BonusManager
 * @brief Orchestration des bonus: apparition, collecte, application/annulation.
 */
class BonusManager {
private:
    GameContext& gameContext_;
    std::shared_ptr<Bonus> currentBonus; 

public:
    /**
     * @brief Construit un gestionnaire de bonus pour un contexte de jeu.
     */
    BonusManager(GameContext& gameContext);
    /**
     * @brief Met à jour les capsules visibles (mouvement + collecte).
     */
    void update();

    /**
     * @brief À appeler lorsqu'un bloc est détruit (peut générer une capsule).
     */
    void onBlockDestroyed(const Block& block);
    /**
     * @brief À appeler lorsqu'une capsule est collectée (applique le bonus).
     */
    void onCapsuleCollected(const Capsule& capsule);
    // pour arkanoid game
 
    
    // Getter methods
    /** @brief Bonus actuellement actif (peut être nul). */
    const std::shared_ptr<Bonus> getCurrentBonus() const { return currentBonus; }
    /** @brief Accès au contexte de jeu sous-jacent. */
    GameContext& getGameContext() { return gameContext_; }
};

#endif // BONUSMANAGER_HPP 