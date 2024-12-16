use nn::{NeuralNetwork, NeuralNetworkConfiguration};

fn main() {
    let xor = NeuralNetwork::new(NeuralNetworkConfiguration {
        n_input_layer: 2,
        n_hidden_layer: 5,
        n_output_layer: 1,
    });
    dbg!(xor);
}
