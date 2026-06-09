# Plano de Trabalho — Parte Visual (Cub-3D)

Este documento descreve o planejamento completo das tarefas da parte visual do projeto (renderização, texturas, eventos e integração com o parser). O objetivo é fornecer um roteiro prático, modular e compatível com a Norma 42.

## Visão geral
- Linguagem: C
- Biblioteca gráfica: miniLibX (local em `minilibx-linux`)
- Requisitos: `cc -Wall -Wextra -Werror -g3`, `norminette`, `valgrind`
- Pastas relevantes: `src/visual/`, `include/`, `src/`, `libft/`

## Entregáveis principais
1. Raycaster com DDA correto e identificação de faces
2. Loader de texturas XPM e mapeamento por coluna
3. Motor de desenho (double buffer) e desenho de colunas texturizadas
4. Eventos (W/A/S/D e rotação) com verificação de colisão
5. Harness de teste (modo de teste) para render local sem parser
6. Integração com parser quando disponível
7. Testes (norminette, valgrind) e documentação mínima

## Roadmap e passos técnicos (ordem sugerida)
1) Preparação do ambiente (já feito)
   - Confirmar `minilibx-linux` compilado e `Makefile` atualizado para usar `-Lminilibx-linux -lmlx`.
   - Comandos úteis:
```bash
cd /home/liferrei/Cub-3d
make            # compila libft + binário
```

2) Harness de teste (modo de teste)
   - Criar função que monta um `t_map` em memória (paredes em anel e algumas texturas test).
   - Inicializar `t_game` com posições do jogador e caminhos XPM de teste.
   - Implementar mecanismo local que monta um `t_map` em memória para desenvolvimento sem parser.
   - Garantir que exista um mecanismo para remover esse código quando o parser real chegar.

3) Implementar DDA e detecção de face
   - Substituir solução passo-a-passo por DDA grid-aligned (calc de stepX/stepY, sideDist, deltaDist).
   - Identificar `face` (N,S,E,W) com base no passo/sinal da normal e se o hit foi em X ou Y.
   - Produzir `t_column_info` com `distance`, `face` e `tex_offset`.

4) Calcular offset de textura e mapeamento vertical
   - Para cada coluna, calcule `lineHeight`, `drawStart`/`drawEnd` e `tex_x` (usando `tex_offset`).
   - Amostrar verticalmente a textura (`tex_y`) com incremento `step = texture.height / lineHeight`.
   - Suportar 4 texturas (NO, SO, WE, EA) indexadas por `face`.

5) Loader de texturas XPM
   - Implementar `texture_load()` chamando `mlx_xpm_file_to_image` e `mlx_get_data_addr`.
   - Tratar erros e liberar com `texture_free()`.

6) Shading por distância e correção de fisheye
   - Aplicar correção: `perpWallDist = side == 0 ? (mapX - posX + (1 - stepX) / 2) / rayDirX : ...`.
   - Escurecer cor com função de atenuação (ex: multiplicar por `1.0 / (1.0 + K * dist)`), sem overflow.

7) Render loop, dupla búffer e performance
   - Renderizar em `t_img` (imagem) e usar `mlx_put_image_to_window` ao fim do frame.
   - Evitar `mlx_pixel_put` por chamada direta do buffer.
   - Opcional: simples limitador de taxa (usar `gettimeofday` e `usleep`).

8) Eventos e movimentação
   - Implementar keydown/keyup e array de estados para WASD + left/right (rotação).
   - `movement_update()` usa `delta_time` para movimentos dependentes de fps.
   - Verificar colisões por checagem de célula antes de atualizar posição.

9) Integração com parser
   - Substituir o harness de teste: ao receber `t_map` do parser, carregar texturas apontadas pelo arquivo .cub.
   - Validar cores F/C e converter para RGB int.

10) Testes e validação
   - Passar `norminette` em todos os arquivos novos.
   - Rodar `valgrind --leak-check=full ./cub3D maps/map.cub` e corrigir vazamentos.

11) Documentação e entrega
   - Atualizar `README.md` com instruções de build/exec e dependências.
   - Documentar pontos relevantes no `PLANO_VISUAL.md`.

## Checklist detalhado (tarefas acionáveis)
- [ ] Confirmar e documentar paths XPM de teste
- [ ] Implementar DDA em `src/visual/raycast.c`
- [ ] Calcular `tex_x`, `tex_y` e amostragem em `src/visual/texture.c`
- [ ] Substituir drawing por buffer em `src/visual/draw.c`
- [ ] Implementar `events_init` e `movement_update` com delta time
- [ ] Adicionar remoção do código de teste (flag/ifdef) para integração final
- [ ] Adicionar scripts: `make norm`, `make valgrind` (opcional)

## Prazos sugeridos (estimates)
- 1-2 dias: Harness de teste, Makefile + MLX local
- 2-4 dias: DDA + render de colunas sem textura
- 2-3 dias: Loader XPM + mapeamento texturizado
- 1-2 dias: Eventos e movimentação
- 1-2 dias: Shading, correções e testes
- 1 dia: Documentação e limpeza final

## Notas de integração e práticas
- Mantenha funções pequenas e em arquivos separados dentro de `src/visual/`.
- Sempre liberar recursos (imagens, texturas, janela) no `renderer_destroy()`.
- Use `libft` para utilitários; evite duplicar funções.
- Teste incrementalmente: render sem textura → textura sem shading → shading.

---

## Responsáveis

- Parte Visual: atribuição confirmada ao membro responsável pela parte visual (sem nomes nem datas).  


Arquivo gerado automaticamente pelo agente. Quando quiser, posso:
- Atualizar o plano com datas exatas e responsáveis por tarefa.
- Gerar `Makefile` targets auxiliares como `make norm` e `make valgrind`.

## Atualizações aplicadas

- Implementado loader XPM e sampler de texturas (`src/visual/texture.c`).
- Corrigido raycaster para fornecer `face`, `tex_offset` e `flip` (`src/visual/raycast.c`).
- Aplicada inversão horizontal de textura quando necessária em `src/visual/renderer.c`.
- Implementado rendering protegido (clamp em `tex_y`) e shading por distância.
- Adicionado controle por estados de tecla e movimento com delta-time (`src/visual/events.c`).
- Adicionado modo `--harness` para testes sem parser e mapa de exemplo em `maps/test_map.cub`.
- Strip de `\n` nas linhas do mapa ao converter lista→matriz para evitar falhas de validação (`src/parsing/parse_map.c`).

## Teste rápido (Linux)

Compile e rode o modo harness:

```bash
make
./cub3D --harness
```

O modo `--harness` cria um mapa mínimo em memória e posiciona o jogador para testes visuais sem precisar de um arquivo `.cub`.

