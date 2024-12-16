pub struct NeuralNetworkConfiguration {
    pub n_input_layer: u32,
    pub n_hidden_layer: u32,
    pub n_output_layer: u32,
}

pub struct Weights {
    dim: (u32, u32),
    weights: Vec<f64>,
}
impl Weights {
    fn new(from: u32, to: u32, initialize: impl Fn() -> f64) -> Weights {
        let weights = (0..from * to).map(|_| initialize()).collect();
        Weights {
            dim: (from, to),
            weights,
        }
    }

    fn get(&self, from: u32, to: u32) -> f64 {
        let idx = (to * self.dim.0 + from) as usize;
        self.weights[idx]
    }

    fn weights_to(&self, to: u32) -> &[f64] {
        let idx = (to * self.dim.0) as usize;
        &self.weights[idx..idx + self.dim.0 as usize]
    }
}
impl std::fmt::Debug for Weights {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for to in 0..self.dim.1 {
            for from in 0..self.dim.0 {
                write!(f, "w_{}{}={} ", to, from, self.get(from, to))?;
            }
        }
        Ok(())
    }
}

#[derive(Debug)]
pub struct NeuralNetwork {
    weights_hidden: Weights,
    weights_output: Weights,
}

impl NeuralNetwork {
    pub fn new(config: NeuralNetworkConfiguration) -> NeuralNetwork {
        NeuralNetwork {
            weights_hidden: Weights::new(config.n_input_layer, config.n_hidden_layer, init_01),
            weights_output: Weights::new(config.n_input_layer, config.n_hidden_layer, init_01),
        }
    }
}

fn init_01() -> f64 {
0.
}
