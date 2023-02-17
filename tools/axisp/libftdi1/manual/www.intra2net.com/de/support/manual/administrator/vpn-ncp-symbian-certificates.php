<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Zertifikate | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn-ncp-symbian.php" title="48. Kapitel - VPN mit dem NCP Client f&uuml;r Symbian"><link rel="prev" href="vpn-ncp-symbian.php" title="48. Kapitel - VPN mit dem NCP Client f&uuml;r Symbian"><link rel="next" href="vpn-ncp-symbian-connection.php" title="48.3. Verbindungen">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="vpn-ncp-symbian-certificates.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-ncp-symbian-certificates.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">48.2. Zertifikate</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-ncp-symbian.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">48. Kapitel - VPN mit dem NCP Client f&uuml;r Symbian</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-ncp-symbian-connection.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-ncp-symbian-certificates"></a>48.2. Zertifikate</h2></div></div></div><p>Der NCP Secure Entry Client kann keine eigenen Zertifikate erstellen. Dies &uuml;bernimmt daher
      das Programm <code class="computeroutput">makecacert</code>, welches im makecert-Paket enthalten
      ist. Der Unterschied zwischen makecacert und makecert ist, dass makecert selbstsignierte
      Zertifikate erzeugt, makecacert dagegen welche, die von einer (dummy) Zertifizierungsstelle (CA)
      signiert wurden.</p><div class="orderedlist"><ol type="1"><li><p> Starten Sie die Batchdatei <code class="computeroutput">makecacert.bat</code> und w&auml;hlen
          eine Laufzeit in Jahren f&uuml;r Ihr Zertifikat.</p><pre class="programlisting">c:\makecert&gt;makecacert.bat
Gueltigkeit des neuen Zertifikats:
1. Ein Jahr
2. Zwei Jahre
3. Drei Jahre
4. Vier Jahre
5. Fuenf Jahre
Ihre Wahl: 5
          
c:\makecert&gt;openssl req -newkey rsa:2048 -days 1825 -x509 -out cacert.pem -keyout
cakey.pem -config openssl-ca.cnf -batch -passout pass:geheim -set_serial 31659
          
Loading 'screen' into random state - done
Generating a 2048 bit RSA private key
............+++
............+++
writing new private key to 'cakey.pem'
-----
          
c:\makecert&gt;openssl req -newkey rsa:2048 -nodes -config openssl.cnf -keyout priv
atekey.pem -out request.pem
Loading 'screen' into random state - done
Generating a 2048 bit RSA private key
.............................................................+++
........................+++
writing new private key to 'privatekey.pem'
-----
        </pre></li><li><p>Sie werden nach den Inhaberdaten des neuen Zertifikats gefragt. Es kommt vor allem
          darauf an, dass die dort eingetragen Daten eindeutig sind und in dieser Form nicht in einem
          anderen Zertifikat verwendet werden. Wir empfehlen, z.B. den Benutzernamen in das Feld
          "Common Name" einzuf&uuml;gen. Hier in diesem Beispiel ist dies "Markus Mustermann".</p><p>Bitte verwenden Sie keine Umlaute und Sonderzeichen, da dies zu Problemen f&uuml;hren
          kann.</p><pre class="programlisting">You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) []:
State or Province Name (full name) []:
Locality Name (eg, city) []:
Organization Name (eg, company) []:
Organizational Unit Name (eg, section) []:
Common Name (eg, your name or your server's hostname) []:Markus Mustermann
Email Address []:

c:\makecert&gt;openssl x509 -days 365 -out newkey_cert.cer -in request.pem -req -CA
cacert.pem -CAkey cakey.pem -set_serial 1 -passin pass:geheim
Loading 'screen' into random state - done
Signature ok
subject=/CN=Markus Mustermann
Getting CA Private Key

c:\makecert&gt;del request.pem

c:\makecert&gt;rem --- please enter the transport password now (just used for trans
port, enter this one while importing) ---

c:\makecert&gt;openssl pkcs12 -export -in newkey_cert.cer -inkey privatekey.pem -ce
rtfile cacert.pem -out newkey.p12
Loading 'screen' into random state - done
        </pre></li><li><p>Als n&auml;chstes m&uuml;ssen Sie ein Passwort f&uuml;r Ihr Zertifikat w&auml;hlen. Mit diesem Passwort
          wird das Zertifikat (und damit der VPN-Zugang) gesch&uuml;tzt. Sie m&uuml;ssen es beim Aufbau der
          VPN-Verbindung eingeben. Verf&uuml;gt Ihr Mobiltelefon nicht &uuml;ber eine QWERTZ-Tastatur, bietet
          es sich an, hier nur Zahlen zu verwenden. Die Standardrichtlinie von NCP verlangt
          mindestens 6 Zahlen oder Zeichen.</p><pre class="programlisting">Enter Export Password:
Verifying - Enter Export Password:

c:\makecert&gt;del privatekey.pem

c:\makecert&gt;del cacert.pem

c:\makecert&gt;del cakey.pem
        </pre></li><li><p>Das Schl&uuml;sselpaket f&uuml;r den Client liegt nun im PKCS#12-Format in der Datei
            <code class="computeroutput">newkey.p12</code>, das Zertifikat f&uuml;r den Intranator
          (PEM-Format) in der Datei <code class="computeroutput">newkey_cert.cer</code>.</p></li><li><p>Starten Sie den Entry Configuration Manager Symbian und &ouml;ffnen das Men&uuml;
            <span class="guimenu">Konfiguration</span>, <span class="guimenuitem">&Uuml;bertrage PKCS#12 Datei zum mobilen
            Ger&auml;t</span>. Kopieren Sie die <code class="filename">newkey.p12</code>-Datei auf das
          mobile Ger&auml;t. Es erscheint die Meldung <code class="computeroutput">Upload wurde erfolgreich
            durchgef&uuml;hrt</code>.</p><div class="mediaobject"><img src="../images/vpn/ncp-symbian/ncp-symbian-copy-client-cert.png"></div></li><li><p>&Ouml;ffnen Sie das Men&uuml; <span class="guimenu">Konfiguration</span>,
            <span class="guimenuitem">Zertifikate</span>. Lassen Sie das Zertifikat aus einer
          PKCS#12-Datei laden und tragen als Pfad
            <strong class="userinput"><code>%INSTALLDIR%\certs\newkey.p12</code></strong> ein.</p><div class="mediaobject"><img src="../images/vpn/ncp-symbian/ncp-symbian-client-cert.png"></div></li><li><p>Als n&auml;chstes muss das Zertifikat des Clients auch dem Intranator bekannt gemacht
          werden. &Ouml;ffnen Sie dazu die Zertifikatsdatei (<code class="filename">newkey_cert.cer</code>) mit
          einem Texteditor (z.B. Wordpad) und &uuml;bernehmen den gesamten Inhalt der Datei in die
          Zwischenablage.</p></li><li><p>&Ouml;ffnen Sie im Intranator das Men&uuml; <span class="guimenu">System&nbsp;&gt;
            Schl&uuml;ssel&nbsp;&gt; Fremde Schl&uuml;ssel</span> und legen einen neuen Schl&uuml;ssel
          an. Vergeben Sie einen Namen f&uuml;r den Schl&uuml;ssel (z.B. den Namen des Mitarbeiters) und f&uuml;gen
          dann die Zertifikatsdaten aus der Zwischenablage in das Feld "Copy &amp; Paste
          Schl&uuml;ssel" ein.</p></li><li><p>Als letztes muss der NCP Client noch das Zertifikat des Intranators bekommen. &Ouml;ffnen
          Sie das Men&uuml; System&nbsp;&gt; Schl&uuml;ssel&nbsp;&gt; Eigene Schl&uuml;ssel und
          w&auml;hlen das Zertifikat aus, das Sie f&uuml;r die Verbindung verwenden wollen. &Uuml;ber den Link
          "Zertifikat exportieren" im Reiter <span class="guisubmenu">Daten</span> kann das Zertifikat in
          eine .pem-Datei gespeichert werden. Speichern Sie Datei in das Verzeichnis des
          makecert-Programms unter dem Namen <code class="filename">vpn_zentrale.pem</code>.</p></li><li><p> Das Zertifikat des Intranators wir nun vom PEM Dateiformat in das f&uuml;r den NCP Client
          f&uuml;r Symbian geeignete DER Format konvertiert. Starten Sie folgenden Befehl im
          makecert-Programmverzeichnis: <strong class="userinput"><code>openssl x509 &#8211;in vpn_zentrale.pem &#8211;inform PEM
            &#8211;out vpn_zentrale.der &#8211;outform DER</code></strong>
        </p></li><li><p>&Ouml;ffnen Sie im <span class="command"><strong>Entry Configuration Manager Symbian</strong></span> das Men&uuml;
            <span class="guimenu">Konfiguration</span>, <span class="guimenuitem">&Uuml;bertrage CA Zertifikat zum mobilen
            Ger&auml;t</span>. Kopieren Sie die <code class="filename">vpn_zentrale.der</code>-Datei auf
          das mobile Ger&auml;t. Es erscheint die Meldung <code class="computeroutput">Upload wurde erfolgreich
            durchgef&uuml;hrt</code>.</p><div class="mediaobject"><img src="../images/vpn/ncp-symbian/ncp-symbian-copy-ca-cert.png"></div><div class="mediaobject"><img src="../images/vpn/ncp-symbian/ncp-symbian-copy-ca-cert2.png"></div></li></ol></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-ncp-symbian.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn-ncp-symbian.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-ncp-symbian-connection.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">48. Kapitel - VPN mit dem NCP Client f&uuml;r Symbian&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;48.3. Verbindungen</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>