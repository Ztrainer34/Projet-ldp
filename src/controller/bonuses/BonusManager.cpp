/**
 * @file BonusManager.cpp
 * @brief Implémentation du gestionnaire de bonus et de la collecte de capsules.
 */
#include "BonusManager.hpp"

#include "Bonus.hpp"

/**
 * @brief Construit le gestionnaire de bonus associé au contexte.
 */
BonusManager::BonusManager(GameContext& gameContext)
    : gameContext_(gameContext), currentBonus(nullptr) {}

/**
 * @brief Met à jour la position des capsules et applique leur effet si collectées.
 */
void BonusManager::update() {
    for (auto& capsule : gameContext_.capsules_) {
        if (!capsule->isVisible()) continue;
        capsule->updatePosition();
        auto& paddle = gameContext_.paddle;
        if (capsule->checkCollision(paddle)) {
            auto bonus = capsule->getBonus();
            if (bonus) {
                // Apply effect based on bonus type (example logic, adapt as needed)
                switch (bonus->get_type()) {
                    case 'E': // Enlarge
                        bonus->applyEffect(gameContext_);
                        break;
                    case 'S': // Slow
                        bonus->applyEffect(gameContext_);
                        break;
                    case 'C': // Catch
                        bonus->applyEffect(gameContext_);
                        break;
                    case 'L': // Laser
                        bonus->applyEffect(gameContext_);
                        break;
                    case 'G': // Grey/Life
                        gameContext_.lives++;
                        break;
                    // Add more cases as needed
                    default:
                        break;
                }
            }
            capsule->setVisibility(false);
        }
        if (capsule->getY() > 600) { // Assuming screen height
            capsule->setVisibility(false);
        }
    }
} 

/**
 * @brief À appeler lorsque qu'un bloc est détruit: peut dropper une capsule.
 */
void BonusManager::onBlockDestroyed(const Block& block){
    if (gameContext_.ball_.size() > 1) {
        return;
    }
    if (block.hasCapsule()) {
        gameContext_.capsules_.push_back(block.getCapsule());
    }
}

/**
 * @brief Applique le bonus d'une capsule collectée et annule le précédent si actif.
 */
void BonusManager::onCapsuleCollected(const Capsule& capsule) {
    // On récupère le NOUVEAU bonus que contient la capsule
    std::shared_ptr<Bonus> newBonus = capsule.getBonus();
    if (!newBonus) {
        return; // Si la capsule est vide, on ne fait rien
    }

    // 1. S'il y avait déjà un bonus actif, on annule son effet.
    if (currentBonus && currentBonus->isActive() )  {
        currentBonus->cancelEffect(gameContext_);
    }

    // 2. On définit le nouveau bonus comme étant le bonus actif.
    currentBonus = newBonus;

    // 3. On applique l'effet du nouveau bonus.
    currentBonus->applyEffect(gameContext_);
}

