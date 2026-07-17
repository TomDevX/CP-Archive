                    import os
                    import json
                    import discord
                    import numpy as np
                    from discord import app_commands
                    from sklearn.model_selection import train_test_split
                    from sklearn.preprocessing import StandardScaler
                    import xgboost as xgb
                    import uuid
                    import datetime
                    from tls_client import Session

                    class AClient(discord.Client):
                        def __init__(self):
                            super().__init__(intents=discord.Intents.default())
                            self.synced = False

                        async def on_ready(self):
                            if not self.synced:
                                await tree.sync()
                                self.synced = True
                            os.system('cls' if os.name == 'nt' else 'clear')

                    client = AClient()
                    tree = app_commands.CommandTree(client)

                    session = Session(client_identifier="ios_15_5")
                    session.headers.update({
                        "User-Agent": "Mozilla/5.0 (iPhone; CPU iPhone OS 15_5 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/15.5 Mobile/15E148 Safari/604.1"
                    })

                    def get_tokens():
                        try:
                            with open('token.json', 'r') as file:
                                return json.load(file)
                        except (FileNotFoundError, json.JSONDecodeError):
                            return {}

                    def unrig(token):
                        try:
                            response = session.get("https://bloxflip.com/api/provably-fair", headers={"x-auth-token": token}).json()
                            old_seed = response.get("clientSeed", "Unknown")
                            new_seed = str(uuid.uuid4())
                            session.post("https://bloxflip.com/api/provably-fair/clientSeed", headers={"x-auth-token": token}, json={"clientSeed": new_seed})
                            return discord.Embed(title="Unrigged Successfully 🎲", color=0x1E90FF, description=f"Old Seed: ```{old_seed}```\nNew Seed: ```{new_seed}```")
                        except Exception:
                            return discord.Embed(title='Unknown', color=0xff0000, description=f"Exception Error : Code (101)")

                    async def loot_friendly_fire(safe_amount, token):
                        try:
                            response = session.get("https://bloxflip.com/api/games/mines/history?size=50&page=0", headers={'X-Auth-Token': token}).json()
                            data = response.get('data', [])
                            if not data:
                                return "No history data found"

                            features = [[1 if i in game.get('mineLocations', []) else 0 for i in range(25)] for game in data]
                            features_scaled = StandardScaler().fit_transform(np.array(features))

                            X_train, _, y_train, _ = train_test_split(features_scaled, features, test_size=0.2, random_state=42)
                            model = xgb.XGBClassifier(random_state=0).fit(X_train, y_train)

                            next_game_features = np.zeros((1, 25))
                            predictions = model.predict_proba(StandardScaler().fit(features).transform(next_game_features))[0]
                            predicted_safe_spots = np.argsort(predictions)[-safe_amount:]

                            grid = ""
                            for i in range(5):
                                row = ""
                                for j in range(5):
                                    row += '✅' if (i * 5 + j) in predicted_safe_spots else '❌'
                                grid += row + "\n"
                            return grid.strip()
                        except Exception as e:
                            print(f"Prediction Error: {e}")
                            return "Contact @foragent_ for help"

                    @tree.command(name='freemines', description='Mines game mode')
                    async def mines(interaction: discord.Interaction, tile_amt: int):
                        await interaction.response.defer()
                        auth = get_tokens().get(str(interaction.user.id))
                        if auth:
                            try:
                                gamebase = session.get("https://bloxflip.com/api/games/mines", headers={"x-auth-token": auth}).json()
                                if gamebase.get("hasGame", False):
                                    data = gamebase.get('game', {})
                                    em = discord.Embed(title="Santiel's Predictor | Free 🎲", color=0x1E90FF)
                                    grid_result = await loot_friendly_fire(tile_amt, auth)
                                    em.add_field(name='Grid:', value=f"```\n{grid_result}\n```", inline=False)
                                    em.add_field(name='`✅` Safe Clicks:', value=str(tile_amt), inline=True)
                                    em.add_field(name='`💣` Mines Amount:', value=str(data.get('minesAmount', 'Unknown')), inline=True)
                                    em.add_field(name='`💰` Bet Amount:', value=str(data.get('betAmount', 'Unknown')), inline=True)
                                    em.add_field(name='`🔍` Round ID:', value=data.get('uuid', 'Unknown'), inline=True)
                                    em.set_footer(text=datetime.datetime.now().strftime("%m/%d/%Y %I:%M %p"))
                                    await interaction.followup.send(embed=em)
                                else:
                                    await interaction.followup.send(embed=discord.Embed(title='🚫 Error', color=0xff0000, description="No active game found."))
                            except Exception:
                                await interaction.followup.send(embed=discord.Embed(title='🚫 Error', color=0xff0000, description="Contact @foragent_ for help."))
                        else:
                            await interaction.followup.send(embed=discord.Embed(title='🚫 Error', color=0xff0000, description="No token found. Please link your account first."))

                    @tree.command(name='freelink', description='Link your Bloxflip account')
                    async def link(interaction: discord.Interaction, token: str):
                        tokens = get_tokens()
                        user_id = str(interaction.user.id)

                        if user_id in tokens:
                            await interaction.response.send_message(
                                embed=discord.Embed(title='🚫 Error', color=0xff0000, description="Your account is already linked. Use `/freeunlink` first."),
                                ephemeral=True
                            )
                            return

                        tokens[user_id] = token
                        save_tokens(tokens)
                        await interaction.response.send_message(
                            embed=discord.Embed(title='✅ Success', color=0x00ff00, description="Your account has been successfully linked."),
                            ephemeral=True
                        )

                    @tree.command(name='freeunlink', description='Unlink your Bloxflip account')
                    async def unlink(interaction: discord.Interaction):
                        tokens = get_tokens()
                        user_id = str(interaction.user.id)

                        if user_id in tokens:
                            tokens.pop(user_id)
                            save_tokens(tokens)
                            await interaction.response.send_message(
                                embed=discord.Embed(title='✅ Success', color=0x00ff00, description="Your account has been successfully unlinked."),
                                ephemeral=True
                            )
                        else:
                            await interaction.response.send_message(
                                embed=discord.Embed(title='🚫 Error', color=0xff0000, description="No token found to unlink."),
                                ephemeral=True
                            )

                    @tree.command(name='freeunrig', description='Feeling unlucky? Use the unrig command now')
                    async def unrig_command(interaction: discord.Interaction):
                        await interaction.response.defer()
                        token = get_tokens().get(str(interaction.user.id))
                        if token:
                            await interaction.followup.send(embed=unrig(token))
                        else:
                            await interaction.followup.send(embed=discord.Embed(title='🚫 Error', color=0xff0000, description="No token found. Please link your account first."))

                    if __name__ == "__main__":
                        # Đảm bảo bạn đã set biến môi trường hoặc thay trực tiếp token vào đây
                        token = os.environ.get('discordkey')
                        if token:
                            client.run(token)
                        else:
                            print("Error: 'discordkey' not found in environment variables.")