EXE = EcosystemSimulation
BUILD_DIR = build

.PHONY: run clean snapshot

run:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
	./$(BUILD_DIR)/$(EXE)
clean:
	rm -rf $(BUILD_DIR) 