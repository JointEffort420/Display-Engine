// GridModel.h
#ifndef DISPLAYENGINE_GRIDMODEL_H
#define DISPLAYENGINE_GRIDMODEL_H

#include <vector>
#include <utility>
#include <memory>
#include <optional>
#include <functional>

#include "CellBuilder.h"
#include "Model.h"

namespace eng {
    class CellModel;
    class ModelFactory;
    struct EngineContext;

    class GridModel : public Model {
    private:
        EngineContext& ctx;
        CellBuilder cellBuilder;
        PolygonViewConfig cellConfig;

        std::vector<std::unique_ptr<CellModel>> cells;       // nullptr slot == dead/empty cell
        std::pair<unsigned int, unsigned int> colRowCount;   // columns, rows

        bool on = false;
        bool walls = true;

        [[nodiscard]] std::optional<std::size_t> resolveIndex(int x, int y) const;
        [[nodiscard]] std::optional<std::size_t> resolveIndex(std::pair<unsigned int, unsigned int> cellCoordinate) const;
        [[nodiscard]] std::pair<float, float> cellPositionFor(const std::pair<unsigned int, unsigned int>& cellCoordinate) const;

        void resizeCells();

    protected:
        CellModel* getMutableCell(const std::pair<unsigned int, unsigned int>& cellCoordinate);

    public:
        GridModel() = delete;
        GridModel(ModelFactory::Key key,
                  EngineContext& ctx,
                  const std::pair<float, float>& position,
                  const std::pair<float, float>& size,
                  const std::pair<unsigned int, unsigned int>& dimensions,
                  CellBuilder cellBuilder,
                  PolygonViewConfig cellConfig,
                  Anchor anchor = Anchor::Center);
        ~GridModel() override;

        void setRowColCount(const std::pair<unsigned int, unsigned int>& rowColCount);
        void toggle();
        void play();
        void pause();
        void setWalls(bool walls);

        void addCell(const std::pair<unsigned int, unsigned int>& cellCoordinate);
        void toggleCell(const std::pair<unsigned int, unsigned int>& cellCoordinate);
        void removeCell(const std::pair<unsigned int, unsigned int>& cellCoordinate);
        void fill();
        void empty();

        [[nodiscard]] std::pair<unsigned int, unsigned int> getCellCoordinate(const std::pair<float, float>& cellWorldPosition) const;
        [[nodiscard]] std::optional<std::size_t> getCellIndex(const std::pair<unsigned int, unsigned int>& cellCoordinate) const;
        [[nodiscard]] std::pair<unsigned int, unsigned int> getRandomCellCoordinate() const;
        [[nodiscard]] const CellModel* getConstCell(const std::pair<unsigned int, unsigned int>& cellCoordinate) const;
        [[nodiscard]] std::pair<unsigned int, unsigned int> getColRowCount() const;
        [[nodiscard]] std::pair<float, float> getCellSize() const;
        [[nodiscard]] const std::vector<std::unique_ptr<CellModel>>& getConstCells() const;
        [[nodiscard]] bool isInBounds(const std::pair<unsigned int, unsigned int>& gridCoordinate) const;
        [[nodiscard]] bool isOn() const;
        [[nodiscard]] bool hasWalls() const;
        [[nodiscard]] unsigned int getNeighbourCount(const std::pair<unsigned int, unsigned int>& cellCoordinate) const;

        void updateModel();
        void calibrateView() override;
        virtual void step() {}
        bool onClick(const std::pair<float, float>& worldCoordinates);
    };
}

#endif //DISPLAYENGINE_GRIDMODEL_H